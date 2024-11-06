#
# Project details
#
project("MessageObjects" VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...")

# Create the library for component
add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/marketdata/MdEntity.cpp
)

# Optionally, specify include (aka #include) directories for this library if component has header files
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/MessageObjects          # Includes the current directory
        ${CMAKE_CURRENT_SOURCE_DIR}/MessageObjects/marketdata
        ${CMAKE_CURRENT_SOURCE_DIR}/MessageObjects/strategies
)