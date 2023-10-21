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

#include <functional>
#include <memory>
#include <vector>
#include <string>

#include <databento/historical.hpp>
#include <databento/log.hpp>

#include "IMarketDataProvider.hpp"
#include "MarketData/Clients/MarketDataStreamingClient.hpp"
#include "MarketData/Processors/MarketDataProcessor.hpp"
#include "CommonServer/Utils/MdTypes.hpp"

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
        std::string clientName;
        std::shared_ptr<databento::Historical> client;
        std::shared_ptr<MarketDataStreamingClient<MarketDataHistoricalClient>> streamingClient;

        static std::vector<std::string> doBatchDownload(const std::shared_ptr<databento::Historical>& _client);

        static std::vector<std::string> readFromFile();

    public:
        MarketDataHistoricalClient() = default;
        explicit MarketDataHistoricalClient(std::string clientName);
        ~MarketDataHistoricalClient() override;

        void subscribe(const Common::MdCallback& callback) override;

        std::function<void ()> getBookUpdate(std::shared_ptr<MarketDataProcessor>& streamingProcessor) override;

        const std::string& getClientName() const;

        std::shared_ptr<IMarketDataProvider> getClient() const override;

        void stop() override;
    };
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP
