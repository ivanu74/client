/**
 * @brief Host logger service entry point.
 *
 * This file is part of HostLogger project.
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

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest_header.h"

#include "config.hpp"
#include "dbus_server.hpp"
#include "http_manager.hpp"
#include "doctest/doctest.h"
#include <getopt.h>

#include <climits>
#include <cstdio>
#include <cstdlib>

// /** @brief Print title with version info. */
//static void printTitle()
//{
//    printf("Http client service " PACKAGE_VERSION ".\n");
//}

/** @brief Application entry point. */
int main(int argc, char* argv[])
{
    int rc;
    // doctest start
    doctest::Context ctx;
    ctx.setOption("abort-after", 5);
    ctx.applyCommandLine(argc, argv);
    ctx.setOption("no-breaks", true);
    ctx.setOption("no-version", true);
    rc = ctx.run();
    if(ctx.shouldExit())
        return rc;
    // doctest end

    // Initialize log manager
    Config config;
    HttpManager httpManager(config);
    // Initialize D-Bus server
    auto bus = sdbusplus::bus::new_default();
    sdbusplus::server::manager_t m{bus, HTTPCLIENT_DBUS_PATH};
    DbusServer dbusMgr(httpManager, bus);
    bus.request_name(HTTPCLIENT_DBUS_IFACE);
    // D-Bus event processing
    while (1) 
    {
        bus.process_discard();
        bus.wait();
    }
    return rc;
}

TEST_CASE("dump_deleteAll" * doctest::skip()) {
    std::ostringstream oss{};
    oss << "busctl --list call "                    // Command
        << "xyz.openbmc_project.Dump.Manager "      // Service
        << "/xyz/openbmc_project/dump "             // Path
        << "xyz.openbmc_project.Collection.DeleteAll DeleteAll"  // Interface Method
        << std::ends;
    CHECK_MESSAGE(std::system(oss.str().c_str()) == 0, 
                  "Delete all dumps. Service phosphor-dump-collect."); // will succsess
}
