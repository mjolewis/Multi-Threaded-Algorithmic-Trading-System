#
# Project details
#
project("StrategyCommon" VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...")

# Create the library for component
add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/OrderManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/StrategyConfigManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/managers/PositionManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/OrderUtil.cpp
)

# Specify the components that MarketData depends on
# Public modifier ensures users of StrategyCommon component also have access to its dependencies
# Link MarketData (aka target) to the components that it depends on
target_link_libraries(${PROJECT_NAME} PRIVATE
        CommonServer
        MessageObjects
)

# Optionally, specify include (aka #include) directories for this library if this component has header files
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/StrategyCommon
        ${CMAKE_CURRENT_SOURCE_DIR}/StrategyCommon/managers
        ${CMAKE_CURRENT_SOURCE_DIR}/StrategyCommon/utils
)