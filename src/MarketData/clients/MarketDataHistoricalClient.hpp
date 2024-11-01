//
// Connects to a market data provider using an HTTP style protocol. This client
// communicates with the providers historical data gateway using the C++ API.
// Historical data can be streamed or loaded data directly into the application.
// The provider also provides an API to make batch download requests, which instructs
// the service to prepare the data as flat files.
//
// Created by Michael Lewis on 9/29/23.
//


#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP

#include <memory>
#include <vector>
#include <string>

#include <databento/historical.hpp>
#include <databento/log.hpp>

#include "IMarketDataProvider.hpp"
#include "MarketData/clients/MarketDataStreamingClient.hpp"
#include "MarketData/processors/MarketDataProcessor.hpp"
#include "CommonServer/logging/Logger.hpp"

namespace BeaconTech::MarketData
{

    // Forward Declarations
    class MarketDataHistoricalClient;

    template<typename T>
    class MarketDataStreamingClient;

    template<typename T>
    class MarketDataConsumer;

    class MarketDataHistoricalClient : public IMarketDataProvider
    {
    private:
        inline static const std::string CLASS = "MarketDataHistoricalClient";

        const BeaconTech::Common::Logger& logger;
        std::string clientName;
        databento::Historical client;
        MarketDataStreamingClient<MarketDataHistoricalClient> streamingClient;

        static std::vector<std::string> doBatchDownload(databento::Historical& _client);

        static std::vector<std::string> readFromFile();

    public:
        MarketDataHistoricalClient(std::string clientName, const BeaconTech::Common::Logger& logger);

        ~MarketDataHistoricalClient() override = default;

        void subscribe(MarketDataHistoricalClient& marketDataClient, const Common::MdCallback& callback);

        std::function<void ()> getBookUpdate(MarketDataProcessor& streamingProcessor) override;

        const std::string& getClientName() const;

        void stop() override;

        // Deleted default ctors and assignment operators
        MarketDataHistoricalClient() = delete;

        MarketDataHistoricalClient(const MarketDataHistoricalClient& other) = delete;

        MarketDataHistoricalClient(MarketDataHistoricalClient&& other) = delete;

        MarketDataHistoricalClient& operator=(const MarketDataHistoricalClient& other) = delete;

        MarketDataHistoricalClient& operator=(MarketDataHistoricalClient&& other) = delete;
    };
} // namespace BeaconTech::marketdata


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP
