/**
 * @brief HttpClient configuration.
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
#include <sstream>

#include <cereal/archives/json.hpp>

#include "dbus_client.hpp"

/** @struct Config
 *  @brief Represent the configuration of the http client.
 */
struct Config
{
  /** @brief Path to archive file. */
  std::string  Service = "true";
  std::string  SerialNumber = "13415456456347456485678567959678989";
  std::string  LogCollectionTimestamp = "Thu Aug 08 14:00:05 MSK 2019";
  std::string  ClientStartTimestamp = ""; //Is not saved
  std::string  SystemType = "vesnin";
  std::string  LogLevel = "System";
  std::string  Originator = "system";
  std::string  SessionID = "dc98fc675cfe7abfad2e0d06b56ace30"; //Is not saved
  std::string  Checksum = "dc98fc675cfe7abfad2e0d06b56ace30";
  std::string  Hostname = "example.com";
  std::string  NotificationManager = "";
  std::string  Cancel = "No";
  std::string  StartTimestamp = "";   //Is not saved
  std::string  FinishTimestamp = "";  //Is not saved

  std::string encode()
  {
    std::ostringstream oss;
    {
      cereal::JSONOutputArchive jsonarchive(oss); // Create an output archive
      jsonarchive(CEREAL_NVP(Service),
                  CEREAL_NVP(SerialNumber),
                  CEREAL_NVP(LogCollectionTimestamp),
                  CEREAL_NVP(ClientStartTimestamp),
                  CEREAL_NVP(SystemType),
                  CEREAL_NVP(LogLevel),
                  CEREAL_NVP(Originator),
                  CEREAL_NVP(SessionID),
                  CEREAL_NVP(Checksum),
                  CEREAL_NVP(Hostname),
                  CEREAL_NVP(NotificationManager),
                  CEREAL_NVP(Cancel),
                  CEREAL_NVP(StartTimestamp),
                  CEREAL_NVP(FinishTimestamp)
                  ); // Write the data to the archive
    }
    return oss.str();
  };

  int loadSettings(DbusClient& dbus)
  {
    dbus.getSetting("Service", Service);
    dbus.getSetting("SerialNumber", SerialNumber);
    dbus.getSetting("LogCollectionTimestamp", LogCollectionTimestamp);
    dbus.getSetting("SystemType", SystemType);
    dbus.getSetting("LogLevel", LogLevel);
    dbus.getSetting("Originator", Originator);
    dbus.getSetting("Checksum", Checksum);
    dbus.getSetting("Hostname", Hostname);
    dbus.getSetting("NotificationManager", NotificationManager);
    dbus.getSetting("Cancel", Cancel);
    return 0;
  }
};

#ifdef DOCTEST_LIBRARY_INCLUDED

TEST_CASE("[config]_loadSettings") {
  DbusClient dbus;
  Config testConfig;
  CHECK(testConfig.loadSettings(dbus) == 0);  
  }

#endif
