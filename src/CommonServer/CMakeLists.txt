#
# Project details
#
project("CommonServer" VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...")

# Create the library for component
add_library(${PROJECT_NAME}  STATIC
        utils/Clock.cpp
        handlers/ConcurrentQueueProcessor.cpp
        datastructures/ConcurrentLockFreeQueue.cpp
        utils/ConfigManager.cpp
        handlers/CLFQProcessor.cpp
        logging/Logger.cpp
)

# Optionally, specify include (aka #include) directories for this library if component has header files
target_include_directories(${PROJECT_NAME}  PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/CommonServer          # Includes the current directory
        ${CMAKE_CURRENT_SOURCE_DIR}/CommonServer/datastructures
        ${CMAKE_CURRENT_SOURCE_DIR}/CommonServer/types
        ${CMAKE_CURRENT_SOURCE_DIR}/CommonServer/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/CommonServer/handlers
        ${CMAKE_CURRENT_SOURCE_DIR}/CommonServer/logging
)