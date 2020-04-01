/**
 * @brief Log manager.
 *
 * This file is part of HttpClient project.
 *
 * Copyright (c) 2018 YADRO
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "doctest/doctest_header.h"

#include "http_manager.hpp"

#include "config.hpp"
#include "http_client.hpp"
#include "dbus_client.hpp"
#include "context.hpp"

#include <iostream> // TODO: test
#include <string>
#include <mutex>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>

std::string getTime(const std::time_t * pt = nullptr);
std::size_t sizeOfFile(const std::string& name);

constexpr auto DUMP_LOG_PATH = "/var/lib/phosphor-debug-collector/dumps/";
constexpr auto EXT1          = ".tar.xz";
constexpr auto EXT2          = ".tar.gz";

//HttpManager::HttpManager()
//{
//  std::cout<<"create HttpManager instance"<<std::endl;    // TODO: test
//}
HttpManager::HttpManager(Config & config): m_config(config)
{
}

int HttpManager::upload(const std::string& path)
{
  std::lock_guard<std::mutex> lock(upload_mutex);
  Context ctx;
  DbusClient dbus;
  m_config.loadSettings(dbus);
  dbus.getSetting("Host", host);
  dbus.getSetting("Port", port);
  if (path.empty()){
    dbus.getSetting("PathOfFile", pathOfFile);
    dbus.getSetting("HttpResource", httpResource);
  }
  std::string localpath{};
  try
  {
    std::cout<<"call upload()"<<std::endl;    // TODO: test
    HTTPClient client(host, port);
    do
    {
      if (!client.requestInfo(ctx, httpResource) && !ctx.ec)
      {
        localpath = logPath(dbus, path);
        lengthOfFile = sizeOfFile(localpath);
        if (pathOfFile.empty() && path.empty())
        {
          dbus.setSetting("PathOfFile", localpath);
        }
          dbus.getSetting("HttpPath", httpPath);
        m_config.ClientStartTimestamp = getTime();
        std::string nameOfFile = std::filesystem::path(localpath).filename();
        if (client.requestNewResourse(ctx, httpResource, httpPath, m_config.encode(), lengthOfFile, nameOfFile) && path.empty())
        {
          dbus.setSetting("HttpResource", httpResource);
        }
      }
      dbus.getSetting("LengthOfBlock", lengthOfBlock);
      while (client.sendFile(ctx, httpResource, localpath, lengthOfBlock));
      if (ctx.ec)
      {
        std::cout << "Error: " << ctx.ec.message() << std::endl;
        return EXIT_FAILURE;
      }
      if (ctx.finished)
      {
        httpResource.clear();
        pathOfFile.clear();
        dbus.setSetting("PathOfFile", pathOfFile);
        dbus.setSetting("HttpResource", httpResource);
        deleteLogs();
        break;
      }
    } while (true);
  } 
  catch (std::exception& e)
  {
      std::cout << "Exception: " << e.what() << std::endl;
      return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

const std::string HttpManager::logPath(DbusClient &dbus, const std::string& path = "") const
{
  std::string localpath{path};
  if (path.empty())
  {
    if (pathOfFile.empty())
    {
      dbus.deleteDump();
      auto entry = dbus.createDump();
      time_t timestamp = dbus.getTimestamp(entry);
      m_config.LogCollectionTimestamp = getTime(&timestamp);
      {
        std::ostringstream filepath;
        filepath << DUMP_LOG_PATH << entry << "/obmcdump_" << entry << "_" << timestamp << EXT1 << std::ends;
        localpath = filepath.str();
      }
      if (!std::filesystem::exists(localpath))
      {
        std::ostringstream filepath;
        filepath << DUMP_LOG_PATH << entry << "/obmcdump_" << entry << "_" << timestamp << EXT2 << std::ends;
        localpath = filepath.str();
      }
      dbus.setSetting("LogCollectionTimestamp", m_config.LogCollectionTimestamp);
    }
    else
    {
      localpath = pathOfFile;
    }
  }
  else
  {
    m_config.LogCollectionTimestamp = getTime();
  }
  std::cout<<"logPath: "<< localpath << std::endl;    // TODO: test
  if (!std::filesystem::exists(localpath))
    throw std::errc::bad_file_descriptor;
  return localpath;
}

void HttpManager::deleteLogs() const
{
  DbusClient dbus;
  dbus.deleteDump();
}

std::string getTime(const std::time_t * pt)
{
  if (pt == nullptr)
  {
  std::time_t t = std::time(nullptr);
  pt = &t;
  }
  std::ostringstream oss;
  oss << std::put_time(std::localtime(pt), "%a %b %d %H:%M:%S %Z %Y"); // get current time
  return oss.str();
}

std::size_t sizeOfFile(const std::string& name)
{
  std::ifstream is(name, std::ifstream::binary);
  if (is)
  {
  // get size of file:
  is.seekg(0, is.end);
  std::size_t size = is.tellg();
  is.close();
  return size;
  }
  throw std::errc::bad_file_descriptor;
}

#ifdef DOCTEST_LIBRARY_INCLUDED

class MyFixture : public HttpManager
{
  Config _config;

  public:
    MyFixture(): HttpManager(_config) {};
};

TEST_CASE("upload" * doctest::skip()) {
  Config config;
  HttpManager httpManager(config);
  CHECK_MESSAGE(httpManager.upload() == 0, "Upload logfile to server."); 
}

TEST_CASE_FIXTURE(MyFixture, "upload_test" * doctest::skip()) {
  CHECK_MESSAGE(upload("test.log") == 0, 
                "Upload test.log to server. Need test.log in current dir."); 
}

TEST_CASE_FIXTURE(MyFixture, "dump_logPath" * doctest::skip()) {
  DbusClient dbus;
  CHECK_MESSAGE(logPath(dbus) != "", "Full path of collected logfile.");
  CHECK_MESSAGE(std::filesystem::path(logPath(dbus)).filename() != "", "FileName of collected logfile.");
}
TEST_CASE_FIXTURE(MyFixture, "logPath_test") {
  DbusClient dbus;
  CHECK_MESSAGE(logPath(dbus, "test.log") == "test.log",
                "Name of collected logfile. Need test.log in current dir.");
  REQUIRE_THROWS(logPath(dbus, "notExist.log"));
}
TEST_CASE("getTime_current") {
  CHECK_MESSAGE(getTime() != "", "Get current Time in Unix format."); 
}
TEST_CASE("sizeOfFile_test") {
  CHECK_MESSAGE(sizeOfFile("test.log") != 0, 
                "Get size of test.log file. Need test.log in current dir.");
  REQUIRE_THROWS(sizeOfFile("notExist.log"));
}

TEST_CASE("getTime_fix") {
  time_t t = 1570005832;
  CHECK_MESSAGE(getTime(&t) == "Wed Oct 02 08:43:52 UTC 2019", "Get Time in Unix format from given time since epoch(1570005832)."); 
}

#endif
