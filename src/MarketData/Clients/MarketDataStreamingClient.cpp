//
// Sets up the market data processor and sets up data streaming
// from the live or historical data from the client
//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP

#include <utility>

#include "MarketDataStreamingClient.hpp"
#include "MarketDataHistoricalClient.hpp"
#include "CommonServer/Utils/MdTypes.hpp"

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the streaming client and downstream components
    template<typename T>
    MarketDataStreamingClient<T>::MarketDataStreamingClient(const T& marketDataClient)
    {
        this->marketDataClient = marketDataClient;
        createStreamingProcessor();
        streamingConsumer = MarketDataConsumer<T>{marketDataClient, streamingProcessor};
    }

    template<typename T>
    MarketDataStreamingClient<T>& MarketDataStreamingClient<T>::operator=(const MarketDataStreamingClient<T>& other)
    {
        // Avoid self-assignment
        if (this == &other) return *this;

        marketDataClient = other.marketDataClient;
        streamingProcessor = other.streamingProcessor;
        streamingConsumer = other.streamingConsumer;

        return *this;
    }

    template<typename T>
    MarketDataStreamingClient<T>& MarketDataStreamingClient<T>::operator=(MarketDataStreamingClient<T>&& other) noexcept
    {
        // Avoid self-assignment
        if (this == &other) return *this;

        marketDataClient = std::move(other.marketDataClient);
        streamingProcessor = std::move(other.streamingProcessor);
        streamingConsumer = std::move(other.streamingConsumer);
    }

    // Creates streaming processors based on an installation configuration
    template<typename T>
    void MarketDataStreamingClient<T>::createStreamingProcessor()
    {
        // Each supported installation will eventually have their own processors. This function
        // will then eventually determine which processor to create based on the installation configuration.
        // Processors should be installation specific because market data and the governing regulations vary
        // across regions, which impacts data attributes in the book update. The processors will be customized
        // to handle these differences appropriately. (Example installations US, EU, CA).
        streamingProcessor = std::make_shared<MarketDataProcessor>();
    }

    // Initialize the processor and consumer. The processor must be initialized before the consumer to avoid
    // missing any book updates that our app consumes from the publisher before the processor is able to handle it
    template<typename T>
    void MarketDataStreamingClient<T>::initialize(const MdCallback& callback)
    {
        streamingProcessor->initialize(callback);
        streamingConsumer.start();
    }
} // namespace BeaconTech::MarketData


#endif