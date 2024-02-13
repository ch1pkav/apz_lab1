//
// Created by vepbxer on 2/13/24.
//

#ifndef APZ_LAB1_COMMON_H
#define APZ_LAB1_COMMON_H

#include <string_view>
#include <format>

namespace common {
    using namespace std::literals;

    static constexpr std::size_t FACADE_PORT = 18080;
    static constexpr std::size_t LOGGING_PORT = 18081;
    static constexpr std::size_t MESSAGE_PORT = 18082;

    static constexpr std::string_view FACADE_ADDR = "http://localhost:18080";
    static constexpr std::string_view LOGGING_ADDR = "http://localhost:18081";
    static constexpr std::string_view MESSAGE_ADDR = "http://localhost:18082";

    enum res {
        OK = 200,
        BAD_REQUEST = 400,
        NOT_FOUND = 404,
        INTERNAL_SERVER_ERROR = 500
    };
}

#endif //APZ_LAB1_COMMON_H
