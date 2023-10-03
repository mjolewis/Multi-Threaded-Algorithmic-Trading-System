//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP

#include "MarketDataStreamingClient.hpp"
#include "MarketDataHistoricalClient.hpp"

namespace MarketData
{
    // Overloaded ctor that initializes the streaming client and downstream components
    template<typename T>
    MarketDataStreamingClient<T>::MarketDataStreamingClient(const T& marketDataClient)
            : marketDataClient{marketDataClient}, streamingProcessor{},
              streamingConsumer{marketDataClient, streamingProcessor}
    {
        createStreamingProcessor();
        streamingConsumer = MarketDataConsumer<T>{marketDataClient, streamingProcessor};
    }

    // Creates streaming processors based on an installation configuration
    template<typename T>
    void MarketDataStreamingClient<T>::createStreamingProcessor()
    {
        // Each supported installation will eventually have their own processors. This method
        // will then eventually determine which processor to create based on an installation configuration.
        // Processors should be region specific because different installations have different regulations
        // and practices that alter the data provided in the book update. The processors will be customized
        // to handle these differences appropriately. (Example installations US, EU, CA).
        streamingProcessor = MarketDataProcessor{};
    }

    // Initializes the processor and consumer. The processor should be initialized before the consumer to avoid
    // missing any book updates that our app consumes from the publisher.
    template<typename T>
    void MarketDataStreamingClient<T>::initialize()
    {
        streamingProcessor.initialize();
        streamingConsumer.start();
    }
}


#endif