cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME apz)
project(${PROJECT_NAME} C CXX)

set(FACADE_NAME ${PROJECT_NAME}_facade)
set(LOGGING_NAME ${PROJECT_NAME}_logging)
set(MESSAGE_NAME ${PROJECT_NAME}_message)

set(CMAKE_CXX_STANDARD 23)

##########################################################
# User configurable options of the template
##########################################################
# Note: symbols like WARNINGS_AS_ERRORS in configuration are intentionally variables
# and not CMake options --using options creates too many problems for students.

#! It is a good practice to set "WARNINGS_AS_ERRORS" ON,
#  but sometimes it creates too much trouble, so default is OFF.
set(WARNINGS_AS_ERRORS OFF)

#! Always use PVS Studio while developing.
set(ENABLE_PVS_STUDIO OFF)

#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of the Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan).
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
#  Info: https://clang.llvm.org/docs/ThreadSanitizer.html
set(ENABLE_TSan OFF)
#! MemorySanitizer -- detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)

#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)

##########################################################
# Project files, packages, libraries and so on
##########################################################

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

##########################################################
# Fixed CMakeLists.txt part
##########################################################

INSTALL(PROGRAMS
				${CMAKE_CURRENT_BINARY_DIR}/${FACADE_NAME}
				${CMAKE_CURRENT_BINARY_DIR}/${LOGGING_NAME}
				${CMAKE_CURRENT_BINARY_DIR}/${MESSAGE_NAME}
				DESTINATION bin)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${FACADE_NAME} ${LOGGING_NAME} ${MESSAGE_NAME})

# Include CMake setup
include(cmake/main-config.cmake)
