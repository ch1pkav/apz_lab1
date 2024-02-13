#include "crow.h"
#include "common.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/").methods(crow::HTTPMethod::Post, crow::HTTPMethod::Get)([](){
        return "Not implemented:(\n";
    });

    app.port(common::MESSAGE_PORT).run();
}