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
namespace server
{

class HttpClient
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
        HttpClient() = delete;
        HttpClient(const HttpClient&) = delete;
        HttpClient& operator=(const HttpClient&) = delete;
        HttpClient(HttpClient&&) = delete;
        HttpClient& operator=(HttpClient&&) = delete;
        virtual ~HttpClient() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        HttpClient(bus::bus& bus, const char* path);



        /** @brief Implementation for Upload
         *  Upload archive file to http server.
         */
        virtual void upload(
            ) = 0;




    private:

        /** @brief sd-bus callback for Upload
         */
        static int _callback_Upload(
            sd_bus_message*, void*, sd_bus_error*);


        static constexpr auto _interface = "xyz.openbmc_project.HttpClient";
        static const vtable::vtable_t _vtable[];
        sdbusplus::server::interface::interface
                _xyz_openbmc_project_HttpClient_interface;
        sdbusplus::SdBusInterface *_intf;


};


} // namespace server
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

