#include <algorithm>
#include <map>
#include <sdbusplus/sdbus.hpp>
#include <sdbusplus/server.hpp>
#include <sdbusplus/exception.hpp>
#include <string>
#include <tuple>
#include <variant>

#include <xyz/openbmc_project/HttpClient/server.hpp>

#include <xyz/openbmc_project/Common/File/error.hpp>

namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace server
{

HttpClient::HttpClient(bus::bus& bus, const char* path)
        : _xyz_openbmc_project_HttpClient_interface(
                bus, path, _interface, _vtable, this), _intf(bus.getInterface())
{
}


int HttpClient::_callback_Upload(
        sd_bus_message* msg, void* context, sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(msg);
#if 1
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif


        auto o = static_cast<HttpClient*>(context);
        o->upload();

        auto reply = m.new_method_return();
        // No data to append on reply.

        reply.method_return();
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        return sd_bus_error_set(error, e.name(), e.description());
    }
    catch(sdbusplus::xyz::openbmc_project::Common::File::Error::Write& e)
    {
        return sd_bus_error_set(error, e.name(), e.description());
    }

    return true;
}

namespace details
{
namespace HttpClient
{
static const auto _param_Upload =
        utility::tuple_to_array(std::make_tuple('\0'));
static const auto _return_Upload =
        utility::tuple_to_array(std::make_tuple('\0'));
}
}




const vtable::vtable_t HttpClient::_vtable[] = {
    vtable::start(),

    vtable::method("Upload",
                   details::HttpClient::_param_Upload
                        .data(),
                   details::HttpClient::_return_Upload
                        .data(),
                   _callback_Upload),
    vtable::end()
};

} // namespace server
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

