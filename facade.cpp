#include "crow.h"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/tokenizer.hpp"
#include "cpr/cpr.h"
#include "common.h"

int main() {
    crow::SimpleApp app;
    auto uuid_generator = boost::uuids::random_generator();

    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Post, crow::HTTPMethod::Get)([&uuid_generator](const crow::request& req){
        if (req.method == crow::HTTPMethod::Post) {
            auto msg = req.url_params.get("message");

            if (!msg)
                return crow::response(common::BAD_REQUEST);

            auto uuid_str = boost::uuids::to_string(uuid_generator());

            std::replace(msg, msg + strlen(msg), ' ', '+');
            cpr::Post(cpr::Url{std::string(common::LOGGING_ADDR) + "?uuid=" + uuid_str + "&message=" + std::string(msg)});

            return crow::response(common::OK);

        } else if (req.method == crow::HTTPMethod::Get) {
            std::string response;

            auto res = cpr::Get(cpr::Url{common::LOGGING_ADDR});

            if (res.status_code != 200)
                return crow::response(common::INTERNAL_SERVER_ERROR);

            response.append(res.text);


            res = cpr::Get(cpr::Url{common::MESSAGE_ADDR});

            if (res.status_code != 200)
                return crow::response(common::INTERNAL_SERVER_ERROR);

            response.append(res.text);

            return crow::response(response);
        } else {
            return crow::response(common::BAD_REQUEST);
        }
    });

    app.port(common::FACADE_PORT).run();
}
