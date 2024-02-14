//
// Created by vepbxer on 2/13/24.
//

#ifndef APZ_LAB1_COMMON_H
#define APZ_LAB1_COMMON_H

#include <string_view>
#include <format>

namespace common {
    static constexpr std::size_t FACADE_PORT = 18080;
    static constexpr std::size_t LOGGING_PORT = 18081;
    static constexpr std::size_t MESSAGE_PORT = 18082;

#ifdef APZ_LOCAL_DEV
    static constexpr std::string_view FACADE_ADDR = "http://0.0.0.0:18080/";
    static constexpr std::string_view LOGGING_ADDR = "http://0.0.0.0:18081/";
    static constexpr std::string_view MESSAGE_ADDR = "http://0.0.0.0:18082/";
#else
    static constexpr std::string_view FACADE_ADDR = "http://apz-facade-1:18080/";
    static constexpr std::string_view LOGGING_ADDR = "http://apz-logging-1:18081/";
    static constexpr std::string_view MESSAGE_ADDR = "http://apz-message-1:18082/";
#endif

    enum res {
        OK = 200,
        BAD_REQUEST = 400,
        NOT_FOUND = 404,
        INTERNAL_SERVER_ERROR = 500
    };
}

#endif //APZ_LAB1_COMMON_H
