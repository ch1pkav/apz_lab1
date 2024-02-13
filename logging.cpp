#include "crow.h"
#include "common.h"
#include <unordered_map>
#include <iostream>

int main() {
    crow::SimpleApp app;
    std::unordered_map<std::string, std::string> log;

    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Post, crow::HTTPMethod::Get)([&log](const crow::request& req){
        if (req.method == crow::HTTPMethod::Get) {
            std::string result;

            for (const auto& [key, value] : log) {
                result += key + ": " + value + '\n';
            }

            return crow::response(result);

        } else if (req.method == crow::HTTPMethod::Post) {

            auto uuid = req.url_params.get("uuid");
            auto message = req.url_params.get("message");

            if (!uuid || !message)
                return crow::response(common::BAD_REQUEST);

            std::cout << uuid << " : " << message << std::endl;
            log[uuid] = message;

            return crow::response(common::OK);
        }
    });

    app.port(common::LOGGING_PORT).run();
}
