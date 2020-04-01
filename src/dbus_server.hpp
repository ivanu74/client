/**
 * @brief Server side implementation of the D-Bus interface
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

#include "http_manager.hpp"

#include <xyz/openbmc_project/HttpClient/server.hpp>

/** @brief D-Bus interface name. */
#define HTTPCLIENT_DBUS_IFACE "xyz.openbmc_project.HttpClient"
/** @brief D-Bus path. */
#define HTTPCLIENT_DBUS_PATH "/xyz/openbmc_project/HttpClient"

// Typedef for super class
using server_inherit = sdbusplus::server::object_t<
    sdbusplus::xyz::openbmc_project::server::HttpClient>;

/** @class DbusServer
 *  @brief D-Bus service by http client.
 */
class DbusServer : public server_inherit
{
  public:
    /** @brief Constructor.
     *
     *  @param[in] httpManager - http manager
     *  @param[in] bus - bus to attach to
     *  @param[in] path - path to attach at, optional, default is
     * HTTPCLIENT_DBUS_PATH
     */
    DbusServer(HttpManager& httpManager, sdbusplus::bus::bus& bus,
               const char* path = HTTPCLIENT_DBUS_PATH);

    // From server_inherit
    void upload();

  private:
    /** @brief Log manager instance. */
    HttpManager& httpManager_;
};
