#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <sdbusplus/bus.hpp>

#include <cstdlib>

using namespace sdbusplus;

constexpr auto DUMP_MGR_SERVICE = "xyz.openbmc_project.Dump.Manager";
constexpr auto DUMP_MGR_PATH = "/xyz/openbmc_project/dump";
constexpr auto DUMP_CREATE_IFACE = "xyz.openbmc_project.Dump.Create";
constexpr auto DUMP_DELETE_IFACE = "xyz.openbmc_project.Collection.DeleteAll";
constexpr auto DUMP_DIR = "/var/lib/phosphor-debug-collector/dumps";
constexpr auto PROPERTY_INTF = "org.freedesktop.DBus.Properties";
constexpr auto DUMP_TIME_PATH = "/xyz/openbmc_project/dump/entry";
constexpr auto DUMP_TIME_IFACE = "xyz.openbmc_project.Time.EpochTime";
constexpr auto DUMP_TIME_PROPERTY = "Elapsed";

constexpr auto SETTINGS_MGR_SERVICE = "xyz.openbmc_project.Settings";
constexpr auto SETTINGS_MGR_PATH = "/xyz/openbmc_project/httpclient/config";
constexpr auto SETTINGS_MGR_IFACE = "xyz.openbmc_project.HttpClient.Config";

class DbusClient
{
  public:
    /** @brief Only need the default DbusClient */
    //DbusClient() = delete;
    ~DbusClient() = default;
    DbusClient(const DbusClient&) = delete;
    DbusClient& operator=(const DbusClient&) = delete;
    DbusClient(DbusClient&&) = delete;
    DbusClient& operator=(DbusClient&&) = delete;


    DbusClient():
        m_bus(bus::new_default_system())
    {

    }

    uint32_t createDump()
    {
      auto m = m_bus.new_method_call(DUMP_MGR_SERVICE, DUMP_MGR_PATH,
                                 DUMP_CREATE_IFACE, "CreateDump");
      auto reply = m_bus.call(m);
      uint32_t entry = 0;
      reply.read(entry);
      std::ostringstream oss{};
      oss << "mapper wait " << DUMP_MGR_PATH << "/entry/" << entry << std::ends;
      // wait object to appear on the dbus
      std::system(oss.str().c_str());
      return entry;
    }

    uint64_t getTimestamp(const uint32_t & entry)
    {
      std::ostringstream path;
      path << DUMP_TIME_PATH << "/" << entry << std::ends;
      auto method = m_bus.new_method_call(DUMP_MGR_SERVICE, path.str().c_str(),
                                          PROPERTY_INTF, "Get");
      method.append(DUMP_TIME_IFACE, DUMP_TIME_PROPERTY);
      auto reply = m_bus.call(method);
      std::variant<uint64_t> property;
      reply.read(property);
      auto value = std::get<uint64_t>(property);
      return value;
    }

    void deleteDump()
    {
      auto m = m_bus.new_method_call(DUMP_MGR_SERVICE, DUMP_MGR_PATH,
                                 DUMP_DELETE_IFACE, "DeleteAll");
      m_bus.call(m);
    }

    template <typename T>
    int getSetting(const std::string& propertyName, T& value)
    {
      sdbusplus::message::variant<T> property;
    
      auto method = m_bus.new_method_call(SETTINGS_MGR_SERVICE, SETTINGS_MGR_PATH,
                                        PROPERTY_INTF, "Get");
    
      method.append(SETTINGS_MGR_IFACE, propertyName);
    
      auto reply = m_bus.call(method);
    
      reply.read(property);
      value = sdbusplus::message::variant_ns::get<T>(property);
      return 0;
    }

    template <typename T>
    void setSetting(const std::string& propertyName, T& value)
    {
      sdbusplus::message::variant<T> propertyValue(value);

      auto method = m_bus.new_method_call(SETTINGS_MGR_SERVICE, SETTINGS_MGR_PATH,
                                        PROPERTY_INTF, "Set");

      method.append(SETTINGS_MGR_IFACE, propertyName, propertyValue);

      m_bus.call(method);
    }

  private:
  sdbusplus::bus::bus m_bus;

};

#ifdef DOCTEST_LIBRARY_INCLUDED

TEST_CASE("[dbus_client]_get") {
  DbusClient dbus;
  std::string path{};
  dbus.getSetting("PathOfFile", path);
  REQUIRE(path == "");
  path = "test.log";
  dbus.setSetting("PathOfFile", path);
  path.clear();
  dbus.getSetting("PathOfFile", path);
  CHECK_MESSAGE(path == "test.log",
                "Name of collected logfile.");
  path.clear();
  dbus.setSetting("PathOfFile", path);
  size_t size;
  CHECK(dbus.getSetting("LengthOfBlock", size) == 0);
  CHECK(dbus.getSetting("Host", path) == 0);
  CHECK(dbus.getSetting("Port", path) == 0);
  CHECK(dbus.getSetting("HttpPath", path) == 0);
  CHECK(dbus.getSetting("HttpResource", path) == 0);
  CHECK(dbus.getSetting("Service", path) == 0);
  CHECK(dbus.getSetting("SerialNumber", path) == 0);
  CHECK(dbus.getSetting("LogCollectionTimestamp", path) == 0);
  CHECK(dbus.getSetting("SystemType", path) == 0);
  CHECK(dbus.getSetting("LogLevel", path) == 0);
  CHECK(dbus.getSetting("Originator", path) == 0);
  CHECK(dbus.getSetting("Checksum", path) == 0);
  CHECK(dbus.getSetting("Hostname", path) == 0);
  CHECK(dbus.getSetting("NotificationManager", path) == 0);
  CHECK(dbus.getSetting("Cancel", path) == 0);  
  }

#endif
