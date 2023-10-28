//
// Sets up the market data processor and sets up data streaming
// from the live or historical data from the client
//
// Created by Michael Lewis on 9/28/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP

#include "memory"

#include "MarketData/processors/MarketDataProcessor.hpp"
#include "MarketData/consumers/MarketDataConsumer.hpp"
#include "CommonServer/typesystem/MdTypes.hpp"

namespace BeaconTech::MarketData
{
    // Forward Declarations
    template<typename T>
    class MarketDataConsumer;

    template<typename T>
    class MarketDataStreamingClient
    {
    private:
        std::shared_ptr<MarketDataProcessor> streamingProcessor;
        MarketDataConsumer<T> streamingConsumer;

    public:
        MarketDataStreamingClient();

        virtual ~MarketDataStreamingClient() = default;

        std::shared_ptr<MarketDataProcessor> createStreamingProcessor();

        void initialize(std::shared_ptr<T> marketDataClient, const Common::MdCallback& callback);

        // Deleted default ctors and assignment operators
        MarketDataStreamingClient(const MarketDataStreamingClient<T>& other) = delete;

        MarketDataStreamingClient(MarketDataStreamingClient<T>&& other) = delete;

        MarketDataStreamingClient<T>& operator=(const MarketDataStreamingClient& other) = delete;

        MarketDataStreamingClient<T>& operator=(MarketDataStreamingClient&& other) = delete;
    };
} // namespace BeaconTech::MarketData


// ********** Start Template Definitions **********
#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
#include "MarketDataStreamingClient.cpp"
#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_CPP
// ********** End Template Definitions **********

#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATASTREAMINGCLIENT_HPP
