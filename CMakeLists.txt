cmake_minimum_required(VERSION 3.27)
set(PROJECT_NAME apz_lab1)
project(${PROJECT_NAME})
set(FACADE_NAME ${PROJECT_NAME}_facade)
set(LOGGING_NAME ${PROJECT_NAME}_logging)
set(MESSAGE_NAME ${PROJECT_NAME}_message)

set(CMAKE_CXX_STANDARD 23)

find_package(Crow)
find_package(Boost 1.71.0 REQUIRED)
set(Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
set(Boost_USE_MULTITHREAD ON)

add_executable(${FACADE_NAME} facade.cpp common.h)
target_link_libraries(${FACADE_NAME} Crow::Crow)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.5)
FetchContent_MakeAvailable(cpr)
target_link_libraries(${FACADE_NAME} cpr::cpr)

add_executable(${LOGGING_NAME} logging.cpp common.h)
target_link_libraries(${LOGGING_NAME} Crow::Crow)

add_executable(${MESSAGE_NAME} message.cpp common.h)
target_link_libraries(${MESSAGE_NAME} Crow::Crow)
