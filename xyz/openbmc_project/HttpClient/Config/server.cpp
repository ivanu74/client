#include <algorithm>
#include <map>
#include <sdbusplus/sdbus.hpp>
#include <sdbusplus/server.hpp>
#include <sdbusplus/exception.hpp>
#include <string>
#include <tuple>
#include <variant>

#include <xyz/openbmc_project/HttpClient/Config/server.hpp>

















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

Config::Config(bus::bus& bus, const char* path)
        : _xyz_openbmc_project_HttpClient_Config_interface(
                bus, path, _interface, _vtable, this), _intf(bus.getInterface())
{
}

Config::Config(bus::bus& bus, const char* path,
                           const std::map<std::string, PropertiesVariant>& vals,
                           bool skipSignal)
        : Config(bus, path)
{
    for (const auto& v : vals)
    {
        setPropertyByName(v.first, v.second, skipSignal);
    }
}




auto Config::pathOfFile() const ->
        std::string
{
    return _pathOfFile;
}

int Config::_callback_get_PathOfFile(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->pathOfFile()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::pathOfFile(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_pathOfFile != value)
    {
        _pathOfFile = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("PathOfFile");
        }
    }

    return _pathOfFile;
}

auto Config::pathOfFile(std::string val) ->
        std::string
{
    return pathOfFile(val, false);
}
int Config::_callback_set_PathOfFile(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->pathOfFile(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_PathOfFile =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::lengthOfBlock() const ->
        uint32_t
{
    return _lengthOfBlock;
}

int Config::_callback_get_LengthOfBlock(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->lengthOfBlock()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::lengthOfBlock(uint32_t value,
                                         bool skipSignal) ->
        uint32_t
{
    if (_lengthOfBlock != value)
    {
        _lengthOfBlock = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("LengthOfBlock");
        }
    }

    return _lengthOfBlock;
}

auto Config::lengthOfBlock(uint32_t val) ->
        uint32_t
{
    return lengthOfBlock(val, false);
}
int Config::_callback_set_LengthOfBlock(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        uint32_t v{};
        m.read(v);
        o->lengthOfBlock(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_LengthOfBlock =
    utility::tuple_to_array(message::types::type_id<
            uint32_t>());
}
}

auto Config::host() const ->
        std::string
{
    return _host;
}

int Config::_callback_get_Host(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->host()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::host(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_host != value)
    {
        _host = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("Host");
        }
    }

    return _host;
}

auto Config::host(std::string val) ->
        std::string
{
    return host(val, false);
}
int Config::_callback_set_Host(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->host(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_Host =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::port() const ->
        std::string
{
    return _port;
}

int Config::_callback_get_Port(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->port()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::port(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_port != value)
    {
        _port = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("Port");
        }
    }

    return _port;
}

auto Config::port(std::string val) ->
        std::string
{
    return port(val, false);
}
int Config::_callback_set_Port(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->port(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_Port =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::httpPath() const ->
        std::string
{
    return _httpPath;
}

int Config::_callback_get_HttpPath(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->httpPath()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::httpPath(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_httpPath != value)
    {
        _httpPath = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("HttpPath");
        }
    }

    return _httpPath;
}

auto Config::httpPath(std::string val) ->
        std::string
{
    return httpPath(val, false);
}
int Config::_callback_set_HttpPath(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->httpPath(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_HttpPath =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::httpResource() const ->
        std::string
{
    return _httpResource;
}

int Config::_callback_get_HttpResource(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->httpResource()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::httpResource(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_httpResource != value)
    {
        _httpResource = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("HttpResource");
        }
    }

    return _httpResource;
}

auto Config::httpResource(std::string val) ->
        std::string
{
    return httpResource(val, false);
}
int Config::_callback_set_HttpResource(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->httpResource(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_HttpResource =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::service() const ->
        std::string
{
    return _service;
}

int Config::_callback_get_Service(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->service()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::service(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_service != value)
    {
        _service = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("Service");
        }
    }

    return _service;
}

auto Config::service(std::string val) ->
        std::string
{
    return service(val, false);
}
int Config::_callback_set_Service(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->service(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_Service =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::serialNumber() const ->
        std::string
{
    return _serialNumber;
}

int Config::_callback_get_SerialNumber(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->serialNumber()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::serialNumber(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_serialNumber != value)
    {
        _serialNumber = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("SerialNumber");
        }
    }

    return _serialNumber;
}

auto Config::serialNumber(std::string val) ->
        std::string
{
    return serialNumber(val, false);
}
int Config::_callback_set_SerialNumber(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->serialNumber(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_SerialNumber =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::logCollectionTimestamp() const ->
        std::string
{
    return _logCollectionTimestamp;
}

int Config::_callback_get_LogCollectionTimestamp(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->logCollectionTimestamp()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::logCollectionTimestamp(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_logCollectionTimestamp != value)
    {
        _logCollectionTimestamp = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("LogCollectionTimestamp");
        }
    }

    return _logCollectionTimestamp;
}

auto Config::logCollectionTimestamp(std::string val) ->
        std::string
{
    return logCollectionTimestamp(val, false);
}
int Config::_callback_set_LogCollectionTimestamp(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->logCollectionTimestamp(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_LogCollectionTimestamp =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::systemType() const ->
        std::string
{
    return _systemType;
}

int Config::_callback_get_SystemType(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->systemType()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::systemType(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_systemType != value)
    {
        _systemType = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("SystemType");
        }
    }

    return _systemType;
}

auto Config::systemType(std::string val) ->
        std::string
{
    return systemType(val, false);
}
int Config::_callback_set_SystemType(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->systemType(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_SystemType =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::logLevel() const ->
        std::string
{
    return _logLevel;
}

int Config::_callback_get_LogLevel(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->logLevel()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::logLevel(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_logLevel != value)
    {
        _logLevel = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("LogLevel");
        }
    }

    return _logLevel;
}

auto Config::logLevel(std::string val) ->
        std::string
{
    return logLevel(val, false);
}
int Config::_callback_set_LogLevel(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->logLevel(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_LogLevel =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::originator() const ->
        std::string
{
    return _originator;
}

int Config::_callback_get_Originator(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->originator()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::originator(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_originator != value)
    {
        _originator = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("Originator");
        }
    }

    return _originator;
}

auto Config::originator(std::string val) ->
        std::string
{
    return originator(val, false);
}
int Config::_callback_set_Originator(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->originator(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_Originator =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::checksum() const ->
        std::string
{
    return _checksum;
}

int Config::_callback_get_Checksum(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->checksum()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::checksum(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_checksum != value)
    {
        _checksum = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("Checksum");
        }
    }

    return _checksum;
}

auto Config::checksum(std::string val) ->
        std::string
{
    return checksum(val, false);
}
int Config::_callback_set_Checksum(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->checksum(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_Checksum =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::hostname() const ->
        std::string
{
    return _hostname;
}

int Config::_callback_get_Hostname(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->hostname()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::hostname(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_hostname != value)
    {
        _hostname = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("Hostname");
        }
    }

    return _hostname;
}

auto Config::hostname(std::string val) ->
        std::string
{
    return hostname(val, false);
}
int Config::_callback_set_Hostname(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->hostname(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_Hostname =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::notificationManager() const ->
        std::string
{
    return _notificationManager;
}

int Config::_callback_get_NotificationManager(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->notificationManager()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::notificationManager(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_notificationManager != value)
    {
        _notificationManager = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("NotificationManager");
        }
    }

    return _notificationManager;
}

auto Config::notificationManager(std::string val) ->
        std::string
{
    return notificationManager(val, false);
}
int Config::_callback_set_NotificationManager(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->notificationManager(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_NotificationManager =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

auto Config::cancel() const ->
        std::string
{
    return _cancel;
}

int Config::_callback_get_Cancel(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    // TODO(venture): Can this except? I wouldn't think so.
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(reply, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        m.append(convertForMessage(o->cancel()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

auto Config::cancel(std::string value,
                                         bool skipSignal) ->
        std::string
{
    if (_cancel != value)
    {
        _cancel = value;
        if (!skipSignal)
        {
            _xyz_openbmc_project_HttpClient_Config_interface.property_changed("Cancel");
        }
    }

    return _cancel;
}

auto Config::cancel(std::string val) ->
        std::string
{
    return cancel(val, false);
}
int Config::_callback_set_Cancel(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    auto o = static_cast<Config*>(context);

    try
    {
        auto m = message::message(value, o->_intf);

#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        std::string v{};
        m.read(v);
        o->cancel(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return o->_intf->sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace Config
{
static const auto _property_Cancel =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

void Config::setPropertyByName(const std::string& _name,
                                     const PropertiesVariant& val,
                                     bool skipSignal)
{
    if (_name == "PathOfFile")
    {
        auto& v = std::get<std::string>(val);
        pathOfFile(v, skipSignal);
        return;
    }
    if (_name == "LengthOfBlock")
    {
        auto& v = std::get<uint32_t>(val);
        lengthOfBlock(v, skipSignal);
        return;
    }
    if (_name == "Host")
    {
        auto& v = std::get<std::string>(val);
        host(v, skipSignal);
        return;
    }
    if (_name == "Port")
    {
        auto& v = std::get<std::string>(val);
        port(v, skipSignal);
        return;
    }
    if (_name == "HttpPath")
    {
        auto& v = std::get<std::string>(val);
        httpPath(v, skipSignal);
        return;
    }
    if (_name == "HttpResource")
    {
        auto& v = std::get<std::string>(val);
        httpResource(v, skipSignal);
        return;
    }
    if (_name == "Service")
    {
        auto& v = std::get<std::string>(val);
        service(v, skipSignal);
        return;
    }
    if (_name == "SerialNumber")
    {
        auto& v = std::get<std::string>(val);
        serialNumber(v, skipSignal);
        return;
    }
    if (_name == "LogCollectionTimestamp")
    {
        auto& v = std::get<std::string>(val);
        logCollectionTimestamp(v, skipSignal);
        return;
    }
    if (_name == "SystemType")
    {
        auto& v = std::get<std::string>(val);
        systemType(v, skipSignal);
        return;
    }
    if (_name == "LogLevel")
    {
        auto& v = std::get<std::string>(val);
        logLevel(v, skipSignal);
        return;
    }
    if (_name == "Originator")
    {
        auto& v = std::get<std::string>(val);
        originator(v, skipSignal);
        return;
    }
    if (_name == "Checksum")
    {
        auto& v = std::get<std::string>(val);
        checksum(v, skipSignal);
        return;
    }
    if (_name == "Hostname")
    {
        auto& v = std::get<std::string>(val);
        hostname(v, skipSignal);
        return;
    }
    if (_name == "NotificationManager")
    {
        auto& v = std::get<std::string>(val);
        notificationManager(v, skipSignal);
        return;
    }
    if (_name == "Cancel")
    {
        auto& v = std::get<std::string>(val);
        cancel(v, skipSignal);
        return;
    }
}

auto Config::getPropertyByName(const std::string& _name) ->
        PropertiesVariant
{
    if (_name == "PathOfFile")
    {
        return pathOfFile();
    }
    if (_name == "LengthOfBlock")
    {
        return lengthOfBlock();
    }
    if (_name == "Host")
    {
        return host();
    }
    if (_name == "Port")
    {
        return port();
    }
    if (_name == "HttpPath")
    {
        return httpPath();
    }
    if (_name == "HttpResource")
    {
        return httpResource();
    }
    if (_name == "Service")
    {
        return service();
    }
    if (_name == "SerialNumber")
    {
        return serialNumber();
    }
    if (_name == "LogCollectionTimestamp")
    {
        return logCollectionTimestamp();
    }
    if (_name == "SystemType")
    {
        return systemType();
    }
    if (_name == "LogLevel")
    {
        return logLevel();
    }
    if (_name == "Originator")
    {
        return originator();
    }
    if (_name == "Checksum")
    {
        return checksum();
    }
    if (_name == "Hostname")
    {
        return hostname();
    }
    if (_name == "NotificationManager")
    {
        return notificationManager();
    }
    if (_name == "Cancel")
    {
        return cancel();
    }

    return PropertiesVariant();
}


const vtable::vtable_t Config::_vtable[] = {
    vtable::start(),
    vtable::property("PathOfFile",
                     details::Config::_property_PathOfFile
                        .data(),
                     _callback_get_PathOfFile,
                     _callback_set_PathOfFile,
                     vtable::property_::emits_change),
    vtable::property("LengthOfBlock",
                     details::Config::_property_LengthOfBlock
                        .data(),
                     _callback_get_LengthOfBlock,
                     _callback_set_LengthOfBlock,
                     vtable::property_::emits_change),
    vtable::property("Host",
                     details::Config::_property_Host
                        .data(),
                     _callback_get_Host,
                     _callback_set_Host,
                     vtable::property_::emits_change),
    vtable::property("Port",
                     details::Config::_property_Port
                        .data(),
                     _callback_get_Port,
                     _callback_set_Port,
                     vtable::property_::emits_change),
    vtable::property("HttpPath",
                     details::Config::_property_HttpPath
                        .data(),
                     _callback_get_HttpPath,
                     _callback_set_HttpPath,
                     vtable::property_::emits_change),
    vtable::property("HttpResource",
                     details::Config::_property_HttpResource
                        .data(),
                     _callback_get_HttpResource,
                     _callback_set_HttpResource,
                     vtable::property_::emits_change),
    vtable::property("Service",
                     details::Config::_property_Service
                        .data(),
                     _callback_get_Service,
                     _callback_set_Service,
                     vtable::property_::emits_change),
    vtable::property("SerialNumber",
                     details::Config::_property_SerialNumber
                        .data(),
                     _callback_get_SerialNumber,
                     _callback_set_SerialNumber,
                     vtable::property_::emits_change),
    vtable::property("LogCollectionTimestamp",
                     details::Config::_property_LogCollectionTimestamp
                        .data(),
                     _callback_get_LogCollectionTimestamp,
                     _callback_set_LogCollectionTimestamp,
                     vtable::property_::emits_change),
    vtable::property("SystemType",
                     details::Config::_property_SystemType
                        .data(),
                     _callback_get_SystemType,
                     _callback_set_SystemType,
                     vtable::property_::emits_change),
    vtable::property("LogLevel",
                     details::Config::_property_LogLevel
                        .data(),
                     _callback_get_LogLevel,
                     _callback_set_LogLevel,
                     vtable::property_::emits_change),
    vtable::property("Originator",
                     details::Config::_property_Originator
                        .data(),
                     _callback_get_Originator,
                     _callback_set_Originator,
                     vtable::property_::emits_change),
    vtable::property("Checksum",
                     details::Config::_property_Checksum
                        .data(),
                     _callback_get_Checksum,
                     _callback_set_Checksum,
                     vtable::property_::emits_change),
    vtable::property("Hostname",
                     details::Config::_property_Hostname
                        .data(),
                     _callback_get_Hostname,
                     _callback_set_Hostname,
                     vtable::property_::emits_change),
    vtable::property("NotificationManager",
                     details::Config::_property_NotificationManager
                        .data(),
                     _callback_get_NotificationManager,
                     _callback_set_NotificationManager,
                     vtable::property_::emits_change),
    vtable::property("Cancel",
                     details::Config::_property_Cancel
                        .data(),
                     _callback_get_Cancel,
                     _callback_set_Cancel,
                     vtable::property_::emits_change),
    vtable::end()
};

} // namespace server
} // namespace HttpClient
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

