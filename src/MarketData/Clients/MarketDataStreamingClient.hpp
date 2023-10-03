//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP

#include "memory"

#include "src/MarketData/Processors/MarketDataProcessor.hpp"
#include "src/MarketData/Consumers/MarketDataConsumer.hpp"

namespace MarketData
{
    // Forward Declarations
    template<typename T>
    class MarketDataConsumer;

    template<typename T>
    class MarketDataStreamingClient
    {
    private:
        T marketDataClient;
        MarketDataProcessor streamingProcessor;
        MarketDataConsumer<T> streamingConsumer;

    public:
        explicit MarketDataStreamingClient(const T& marketDataClient);
        virtual ~MarketDataStreamingClient() = default;

        void createStreamingProcessor();
        void initialize();
    };
}

// ********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#include "MarketDataStreamingClient.cpp"
#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
// ********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP
