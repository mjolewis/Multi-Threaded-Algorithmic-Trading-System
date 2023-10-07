//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP

#include "MarketDataStreamingClient.hpp"
#include "MarketDataHistoricalClient.hpp"

namespace BeaconTech::MarketData
{
    // Overloaded ctor that initializes the streaming client and downstream components
    template<typename T>
    MarketDataStreamingClient<T>::MarketDataStreamingClient(const T& marketDataClient)
            : marketDataClient{marketDataClient}, streamingProcessor{},
              streamingConsumer{marketDataClient, streamingProcessor}
    {
        createStreamingProcessor();
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
        streamingProcessor = MarketDataProcessor{};
    }

    // Initialize the processor and consumer. The processor must be initialized before the consumer to avoid
    // missing any book updates that our app consumes from the publisher before the processor is able to handle it
    template<typename T>
    void MarketDataStreamingClient<T>::initialize()
    {
        streamingProcessor.initialize();
        streamingConsumer.start();
    }
} // namespace BeaconTech::MarketData


#endif