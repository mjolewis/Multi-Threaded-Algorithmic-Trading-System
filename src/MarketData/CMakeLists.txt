#
# Project details
#
project("MarketData" VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "Started CMake for ${PROJECT_NAME} v${PROJECT_VERSION}...")

# Start Databento Dependency
include(FetchContent)

FetchContent_Declare(
        databento
        GIT_REPOSITORY https://github.com/databento/databento-cpp
        GIT_TAG HEAD
)
FetchContent_MakeAvailable(databento)
# End Databento Dependency

# Create the library for component
add_library(${PROJECT_NAME} STATIC
        OrderBook.cpp
        MarketDataUtils.cpp
        processors/MarketDataProcessor.cpp
        consumers/MarketDataConsumer.cpp
        clients/MarketDataHistoricalClient.cpp
        clients/MarketDataStreamingClient.cpp
        clients/MarketDataStreamingClient.hpp
        clients/MarketDataLiveClient.cpp
)

# Specify the components that MarketData depends on
# Public modifier ensures users of MarketData component also have access to its dependencies
# Link MarketData (aka target) to the components that it depends on
target_link_libraries(${PROJECT_NAME} PUBLIC
        CommonServer
        MessageObjects
        databento::databento
)

# Optionally, specify include (aka #include) directories for this library if this component has header files
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/MarketData
        ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/processors
        ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/consumers
        ${CMAKE_CURRENT_SOURCE_DIR}/MarketData/clients
)