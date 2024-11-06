cmake_minimum_required(VERSION 3.26)

#
# Project details
#
project("BeaconTech" VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...")

#
# Main project check
#

set(IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(IS_MAIN_PROJECT ON)
endif()

#
# Prevent building in the source directory
#
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

#
# Compiler details
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Wpedantic -O2") # -Werror -fsanitize=address
# Specific flags for Release mode
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
set(CMAKE_VERBOSE_MAKEFILE on)

#
# Model project dependencies
#

# Start Boost Dependency
set(BOOST_INCLUDE /usr/local/Cellar/boost/1.81.0)
set(BOOST_LIBRARY /usr/local/Cellar/boost/1.81.0)
find_package(Boost 1.81.0)
include_directories(${Boost_INCLUDE_DIR})

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
# End Boost dependency

# Add the component directories as subdirectories
add_subdirectory(src/CommonServer)
add_subdirectory(src/MessageObjects)
add_subdirectory(src/MarketData)
add_subdirectory(src/StrategyCommon)
add_subdirectory(src/Strategies)
add_subdirectory(src/RiskManager)

#include_directories(${PROJECT_SOURCE_DIR})
#include_directories(${PROJECT_SOURCE_DIR}/src)

## Add the src directory to the include path for all subdirectories
#include_directories(src)

#add_library(
#        ${PROJECT_NAME}
#)

# Specify the components that root depends on
# Link src (aka target) to the components that it depends on
#target_link_libraries(
#        ${PROJECT_NAME}
#        PUBLIC
#        date::date
#        httplib::httplib
#        nlohmann_json::nlohmann_json
#        OpenSSL::Crypto
#        OpenSSL::SSL
#        Threads::Threads
#        ${ZSTD_TARGET}
#)

#
# Provide alias to library for
#

#add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
#
#verbose_message("Project is now aliased as ${PROJECT_NAME}::${PROJECT_NAME}.")

#
# Install license
#

install(
        FILES
        "LICENSE"
        DESTINATION
        ${CMAKE_INSTALL_DATADIR}/licenses/${PROJECT_NAME}
)

