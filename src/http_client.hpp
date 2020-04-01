#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <boost/asio/ts/internet.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/erase.hpp>

#include <boost/beast.hpp>

#include <cereal/external/base64.hpp>

#include "context.hpp"
#include <system_error>

namespace http = boost::beast::http;

class HTTPClient
{
  public:
    /** @brief Only need the default HTTPClient */
    HTTPClient() = delete;
    ~HTTPClient() = default;
    HTTPClient(const HTTPClient&) = delete;
    HTTPClient& operator=(const HTTPClient&) = delete;
    HTTPClient(HTTPClient&&) = delete;
    HTTPClient& operator=(HTTPClient&&) = delete;


    HTTPClient(const std::string& host, const std::string& port):
        m_ep(boost::asio::ip::address::from_string(host), boost::lexical_cast<int>(port)),
        m_sock(m_ios)
    {
        m_sock.open(m_ep.protocol());
    }
    void connect() 
    {
      m_sock.connect(m_ep);
    }
    void close() 
    {
      m_sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
      m_sock.close();
    }
  /** Send POST request to tus-server */
  bool requestNewResourse(Context& ctx, std::string& resourse, const std::string& path, const std::string& metadata,
                          const std::size_t length, const std::string name) 
  {
    if (path.empty() || !resourse.empty() || ctx.ec)
    {
      return false;
    }
    //std::size_t length = 10;
    std::size_t offset = 0;
    // Set up extra header fields for request message
    std::map<std::string, std::string> fields;
    fields["Tus-Resumable"] = tus_version;
    fields["Upload-length"] = std::to_string(length);
    fields["Upload-Metadata"] = "data " + base64encode(metadata) + ",filename " + base64encode(name);
    http::response<http::dynamic_body> msg;
    const char* body = nullptr;
    // Send the HTTP request to the remote host
    HTTPRequest(http::verb::post, path, fields, msg, body, 0);
    if (msg.base().result_int() == 500)
    {
      std::cout << "requestNewResourse. Response returned with status code " 
        << msg.base().result_int() << "\n";
      ctx.ec = std::make_error_code(std::errc::bad_message);
      return false;
    }
    // Check that response is OK.
    if (msg.base().result_int() != 201)
    {
      std::cout << "requestNewResourse. Response returned with status code " 
        << msg.base().result_int() << "\n";
      ctx.ec = std::make_error_code(std::errc::resource_unavailable_try_again);
      return false;
    }
    // Try to get field <Location>
    resourse = findField(msg, "Location");
    if (!resourse.empty())
    {
      std::cout << "Location: " << resourse << std::endl;  // TODO: test
      m_length = length;
      m_offset = offset;
    }
    return !resourse.empty();
  }

  bool requestInfo(Context& ctx, const std::string& path) 
  {
    if (path.empty() || ctx.ec)
    {
      return false;
    }
    // Set up extra header fields for request message
    std::map<std::string, std::string> fields;
    fields["Tus-Resumable"] = tus_version;
    http::response<http::dynamic_body> msg;
    const char* body = nullptr;
    // Send the HTTP request to the remote host
    HTTPRequest(http::verb::head, path, fields, msg, body, 0);
    //std::cout << "Msg response:\n" << msg << std::endl;  // TODO: test response of GET
    // std::cout << "Msg status: " << msg.base().result_int() << std::endl; // TODO: test status response of GET
    // Check that response is OK.
    if (msg.base().result_int() == 200)
    {
      // Find field <Upload-Length> and <Upload-Offset>
      //std::cout << "Response returned with status code " << msg.base().result_int() << "\n";
      auto length = boost::lexical_cast<std::size_t>(findField(msg, "Upload-Length"));
      auto offset = boost::lexical_cast<std::size_t>(findField(msg, "Upload-Offset"));
      auto meta = findField(msg, "Upload-Metadata");
      //std::cout << "Upload-Length: " << length << std::endl;
      if (length != 0 && length > offset && checkMetadata(meta))
      {
        m_length = length;
        m_offset = offset;
        return true;
      }
      if (length != 0 && length == offset && checkMetadata(meta))  // If file upload is finished, then start new upload.
      {
        ctx.finished = true;
        return true;
      }
      ctx.ec = std::make_error_code(std::errc::invalid_argument);
      return true;
    }
    if (msg.base().result_int() == 500)
    {
    std::cout << "Response returned with status code " << msg.base().result_int() << "\n";
    ctx.ec = std::make_error_code(std::errc::operation_canceled);
    return true;
    }
    std::cout << "Response returned with status code " << msg.base().result_int() << "\n";
    ctx.ec = std::make_error_code(std::errc::not_connected);
    return true;
  }

  bool sendFile(Context& ctx, const std::string& path, const std::string& nameOfFile, std::size_t lengthOfBlock) 
  {
    if (path.empty() || nameOfFile.empty() || ctx.ec || ctx.finished)
    {
      return false;
    }
    http::response<http::dynamic_body> msg;
    {
      std::map<std::string, std::string> fields;
      fields["Tus-Resumable"] = tus_version;
      fields["Upload-Offset"] = std::to_string(m_offset);
      fields["Content-Type"]  = "application/offset+octet-stream";
      // create buffer for data
      std::unique_ptr<char[]> bodybuf(new char[lengthOfBlock]);
      // read block of data:
      auto sizeOfBody = readLog(nameOfFile, bodybuf.get(), lengthOfBlock);
      // Send the HTTP request to the remote host
      HTTPRequest(http::verb::patch, path, fields, msg, bodybuf.get(), sizeOfBody);
    }
    // Check that response is OK.
    //std::cout << "Msg response:\n" << msg << std::endl;  // TODO: test response of GET
    if (msg.base().result_int() != 204)
    {
      std::cout << "sendFile. Response returned with status code " 
        << msg.base().result_int() << "\n";
      ctx.ec = std::make_error_code(std::errc::resource_unavailable_try_again);
      return false;
    }
    const auto value = findField(msg, "Upload-Offset");
    if (value.empty())
    {
      ctx.ec = std::make_error_code(std::errc::bad_message);
      return false;
    }
    auto offset = boost::lexical_cast<std::size_t>(value);
    if (offset < m_length)
    {
      m_offset = offset;
      return true;
    }
    if (offset == m_length)
    {
      ctx.finished = true;
      return false;
    }
    //std::cout << "sendFile. status code: " << msg.base().result_int() << std::endl;
    ctx.ec = std::make_error_code(std::errc::resource_unavailable_try_again);
    return false;
  }

  private:
  boost::asio::io_context m_ios;
  boost::asio::ip::tcp::endpoint m_ep;
  boost::asio::ip::tcp::socket m_sock;

  const int version = 11;
  const std::string tus_version = "1.0.0"; 

  std::size_t m_length{0};
  std::size_t m_offset{0};

  template<bool isRequest, class Body, class Allocator>
  std::string findField(http::message<
    isRequest,
    Body,
    http::basic_fields<Allocator>>& msg,
    const std::string& field)
  {
    auto it = msg.find(field);
    if(it == msg.end())
    {
      return std::string{};
    }
    return it->value().to_string();
  }

  template<bool isRequest, class Body, class Allocator>
  int HTTPRequest(
    http::verb method,
    const std::string& path,
    const std::map<std::string, std::string>& fields,
    http::message<isRequest, Body, http::basic_fields<Allocator>>& msg,
    const char* body,
    std::size_t sizeOfBody
    )
  {
    //_s.expires_after(std::chrono::seconds(30));
    connect();
    // Set up an HTTP request message
    http::request<http::dynamic_body> req{method, path, version};
    req.set(http::field::host, m_ep.address().to_string());
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set(http::field::accept, "*/*");
    req.set(http::field::connection, "close");
    for (const auto& [key, value] : fields)
    {
      req.set(key, value);
    }
    if (sizeOfBody > 0)
    {
      boost::beast::ostream(req.body()).write(body, sizeOfBody);
      req.set(http::field::content_length, req.body().size());
    }
    // Send the HTTP request to the remote host
    http::write(m_sock, req);
    // Receive the HTTP response
    boost::beast::flat_buffer buffer;
    http::read(m_sock, buffer, msg);
    close();
    return 0;
  }

  bool checkMetadata(std::string metadata)
  {
    return true;
  }

  std::string base64encode(std::string data)
  {
    //boost::erase_all(data, " ");  // TODO: need to remain whitespace in "LogCollectionTimestamp"
    boost::erase_all(data, "\n");
    return cereal::base64::encode(reinterpret_cast<const unsigned char *>(data.c_str()), data.size());
  }

  std::size_t readLog(const std::string& nameOfFile, char* bodybuf, std::size_t lengthOfBlock)
  {
    std::ifstream is(nameOfFile, std::ifstream::binary);
    if (!is)
    {
      throw std::errc::bad_file_descriptor;
    }
    is.seekg(m_offset);
    // read data as a block:
    return is.readsome(bodybuf, lengthOfBlock);
  }
};
