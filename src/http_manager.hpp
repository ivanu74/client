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

#pragma once

#include <string>
#include <mutex>

class DbusClient;
struct Config;

/** @class HttpManager
 *  @brief Http manager.
 *         All functions within this class are not thread-safe.
 */
class HttpManager
{
  public:
    /** @brief Only need the default HttpManager */
    HttpManager() = delete;
    ~HttpManager() = default;
    HttpManager(const HttpManager&) = delete;
    HttpManager& operator=(const HttpManager&) = delete;
    HttpManager(HttpManager&&) = delete;
    HttpManager& operator=(HttpManager&&) = delete;


    /** @brief Constructor. */
    explicit HttpManager(Config & config);

    /** @brief Upload archive file: upload archive to a server.
     *
     *  @return error code, 0 if operation completed successfully
     */
    int upload()
    {
      return upload("");
    }
    

  protected:
    /** @brief Upload archive file: upload archive to a server.
     *
     *  @param[in] path - path to file of archive
     *  @return error code, 0 if operation completed successfully
     */
    int upload(const std::string& path);

    /** @brief Prepare the path to archive file.
     *
     * @return path to archive file including its name
     */
    const std::string logPath(DbusClient& dbus, const std::string& path) const;
    /** @brief Delete all archive files.
     *
     */
    void deleteLogs() const;

  private:
    Config & m_config;
    // Saved in Settings service
    std::string pathOfFile;
    std::size_t lengthOfBlock = 100000;
    std::string host = "10.0.2.2";
    std::string port = "8080";
    std::string httpPath = "/files/";
    std::string httpResource;

    std::size_t lengthOfFile;
    std::mutex upload_mutex;
};
