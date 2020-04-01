#pragma once
#include <map>
#include <string>
#include <sdbusplus/sdbus.hpp>
#include <sdbusplus/server.hpp>
#include <systemd/sd-bus.h>
#include <tuple>
#include <variant>

















namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace HttpClient
{
namespace server
{

class Config
{
    public:
        /* Define all of the basic class operations:
         *     Not allowed:
         *         - Default constructor to avoid nullptrs.
         *         - Copy operations due to internal unique_ptr.
         *         - Move operations due to 'this' being registered as the
         *           'context' with sdbus.
         *     Allowed:
         *         - Destructor.
         */
        Config() = delete;
        Config(const Config&) = delete;
        Config& operator=(const Config&) = delete;
        Config(Config&&) = delete;
        Config& operator=(Config&&) = delete;
        virtual ~Config() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Config(bus::bus& bus, const char* path);


        using PropertiesVariant = std::variant<
                uint32_t,
                std::string>;

        /** @brief Constructor to initialize the object from a map of
         *         properties.
         *
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         *  @param[in] vals - Map of property name to value for initialization.
         */
        Config(bus::bus& bus, const char* path,
                     const std::map<std::string, PropertiesVariant>& vals,
                     bool skipSignal = false);



        /** Get value of PathOfFile */
        virtual std::string pathOfFile() const;
        /** Set value of PathOfFile with option to skip sending signal */
        virtual std::string pathOfFile(std::string value,
               bool skipSignal);
        /** Set value of PathOfFile */
        virtual std::string pathOfFile(std::string value);
        /** Get value of LengthOfBlock */
        virtual uint32_t lengthOfBlock() const;
        /** Set value of LengthOfBlock with option to skip sending signal */
        virtual uint32_t lengthOfBlock(uint32_t value,
               bool skipSignal);
        /** Set value of LengthOfBlock */
        virtual uint32_t lengthOfBlock(uint32_t value);
        /** Get value of Host */
        virtual std::string host() const;
        /** Set value of Host with option to skip sending signal */
        virtual std::string host(std::string value,
               bool skipSignal);
        /** Set value of Host */
        virtual std::string host(std::string value);
        /** Get value of Port */
        virtual std::string port() const;
        /** Set value of Port with option to skip sending signal */
        virtual std::string port(std::string value,
               bool skipSignal);
        /** Set value of Port */
        virtual std::string port(std::string value);
        /** Get value of HttpPath */
        virtual std::string httpPath() const;
        /** Set value of HttpPath with option to skip sending signal */
        virtual std::string httpPath(std::string value,
               bool skipSignal);
        /** Set value of HttpPath */
        virtual std::string httpPath(std::string value);
        /** Get value of HttpResource */
        virtual std::string httpResource() const;
        /** Set value of HttpResource with option to skip sending signal */
        virtual std::string httpResource(std::string value,
               bool skipSignal);
        /** Set value of HttpResource */
        virtual std::string httpResource(std::string value);
        /** Get value of Service */
        virtual std::string service() const;
        /** Set value of Service with option to skip sending signal */
        virtual std::string service(std::string value,
               bool skipSignal);
        /** Set value of Service */
        virtual std::string service(std::string value);
        /** Get value of SerialNumber */
        virtual std::string serialNumber() const;
        /** Set value of SerialNumber with option to skip sending signal */
        virtual std::string serialNumber(std::string value,
               bool skipSignal);
        /** Set value of SerialNumber */
        virtual std::string serialNumber(std::string value);
        /** Get value of LogCollectionTimestamp */
        virtual std::string logCollectionTimestamp() const;
        /** Set value of LogCollectionTimestamp with option to skip sending signal */
        virtual std::string logCollectionTimestamp(std::string value,
               bool skipSignal);
        /** Set value of LogCollectionTimestamp */
        virtual std::string logCollectionTimestamp(std::string value);
        /** Get value of SystemType */
        virtual std::string systemType() const;
        /** Set value of SystemType with option to skip sending signal */
        virtual std::string systemType(std::string value,
               bool skipSignal);
        /** Set value of SystemType */
        virtual std::string systemType(std::string value);
        /** Get value of LogLevel */
        virtual std::string logLevel() const;
        /** Set value of LogLevel with option to skip sending signal */
        virtual std::string logLevel(std::string value,
               bool skipSignal);
        /** Set value of LogLevel */
        virtual std::string logLevel(std::string value);
        /** Get value of Originator */
        virtual std::string originator() const;
        /** Set value of Originator with option to skip sending signal */
        virtual std::string originator(std::string value,
               bool skipSignal);
        /** Set value of Originator */
        virtual std::string originator(std::string value);
        /** Get value of Checksum */
        virtual std::string checksum() const;
        /** Set value of Checksum with option to skip sending signal */
        virtual std::string checksum(std::string value,
               bool skipSignal);
        /** Set value of Checksum */
        virtual std::string checksum(std::string value);
        /** Get value of Hostname */
        virtual std::string hostname() const;
        /** Set value of Hostname with option to skip sending signal */
        virtual std::string hostname(std::string value,
               bool skipSignal);
        /** Set value of Hostname */
        virtual std::string hostname(std::string value);
        /** Get value of NotificationManager */
        virtual std::string notificationManager() const;
        /** Set value of NotificationManager with option to skip sending signal */
        virtual std::string notificationManager(std::string value,
               bool skipSignal);
        /** Set value of NotificationManager */
        virtual std::string notificationManager(std::string value);
        /** Get value of Cancel */
        virtual std::string cancel() const;
        /** Set value of Cancel with option to skip sending signal */
        virtual std::string cancel(std::string value,
               bool skipSignal);
        /** Set value of Cancel */
        virtual std::string cancel(std::string value);

        /** @brief Sets a property by name.
         *  @param[in] _name - A string representation of the property name.
         *  @param[in] val - A variant containing the value to set.
         */
        void setPropertyByName(const std::string& _name,
                               const PropertiesVariant& val,
                               bool skipSignal = false);

        /** @brief Gets a property by name.
         *  @param[in] _name - A string representation of the property name.
         *  @return - A variant containing the value of the property.
         */
        PropertiesVariant getPropertyByName(const std::string& _name);


    private:

        /** @brief sd-bus callback for get-property 'PathOfFile' */
        static int _callback_get_PathOfFile(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'PathOfFile' */
        static int _callback_set_PathOfFile(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'LengthOfBlock' */
        static int _callback_get_LengthOfBlock(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'LengthOfBlock' */
        static int _callback_set_LengthOfBlock(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Host' */
        static int _callback_get_Host(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Host' */
        static int _callback_set_Host(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Port' */
        static int _callback_get_Port(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Port' */
        static int _callback_set_Port(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'HttpPath' */
        static int _callback_get_HttpPath(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'HttpPath' */
        static int _callback_set_HttpPath(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'HttpResource' */
        static int _callback_get_HttpResource(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'HttpResource' */
        static int _callback_set_HttpResource(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Service' */
        static int _callback_get_Service(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Service' */
        static int _callback_set_Service(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'SerialNumber' */
        static int _callback_get_SerialNumber(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'SerialNumber' */
        static int _callback_set_SerialNumber(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'LogCollectionTimestamp' */
        static int _callback_get_LogCollectionTimestamp(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'LogCollectionTimestamp' */
        static int _callback_set_LogCollectionTimestamp(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'SystemType' */
        static int _callback_get_SystemType(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'SystemType' */
        static int _callback_set_SystemType(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'LogLevel' */
        static int _callback_get_LogLevel(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'LogLevel' */
        static int _callback_set_LogLevel(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Originator' */
        static int _callback_get_Originator(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Originator' */
        static int _callback_set_Originator(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Checksum' */
        static int _callback_get_Checksum(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Checksum' */
        static int _callback_set_Checksum(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Hostname' */
        static int _callback_get_Hostname(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Hostname' */
        static int _callback_set_Hostname(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'NotificationManager' */
        static int _callback_get_NotificationManager(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'NotificationManager' */
        static int _callback_set_NotificationManager(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Cancel' */
        static int _callback_get_Cancel(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Cancel' */
        static int _callback_set_Cancel(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);


        static constexpr auto _interface = "xyz.openbmc_project.HttpClient.Config";
        static const vtable::vtable_t _vtable[];
        sdbusplus::server::interface::interface
                _xyz_openbmc_project_HttpClient_Config_interface;
        sdbusplus::SdBusInterface *_intf;

        std::string _pathOfFile{};
        uint32_t _lengthOfBlock = 100000;
        std::string _host = "10.0.2.2";
        std::string _port = "8080";
        std::string _httpPath = "/files/";
        std::string _httpResource = "";
        std::string _service = "true";
        std::string _serialNumber = "13415456456347456485678567959678989";
        std::string _logCollectionTimestamp = "Thu Aug 08 14:00:05 MSK 2019";
        std::string _systemType = "vesnin";
        std::string _logLevel = "System";
        std::string _originator = "system";
        std::string _checksum = "dc98fc675cfe7abfad2e0d06b56ace30";
        std::string _hostname = "example.com";
        std::string _notificationManager = "";
        std::string _cancel = "No";

};


} // namespace server
} // namespace HttpClient
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

