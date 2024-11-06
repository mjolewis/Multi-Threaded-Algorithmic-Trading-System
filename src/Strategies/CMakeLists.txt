cmake_minimum_required(VERSION 3.26)

#
# Project details
#
project("Strategies" VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...")

add_executable(${PROJECT_NAME} StrategyMain.cpp
        algos/FeatureEngine.cpp
)

# Link Strategies (aka target) to the components that it depends on
target_link_libraries(${PROJECT_NAME} PRIVATE
        CommonServer
        MessageObjects
        MarketData
        StrategyCommon
)

# Optionally, specify include (aka #include) directories for this library if component has header files
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Strategies          # Includes the current directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Strategies/algos
)