//
// Connects to a market data provider using a subscription style protocol. This client
// communicates with the providers real-time data gateway using the C++ API.
//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP

#include <memory>
#include <string>

#include <databento/live.hpp>

#include "IMarketDataProvider.hpp"
#include "MarketDataStreamingClient.hpp"
#include "CommonServer/logging/Logger.hpp"

namespace BeaconTech::MarketData
{

    // Forward Declarations
    class MarketDataLiveClient;

    template<typename T>
    class MarketDataStreamingClient;

    template<typename T>
    class MarketDataConsumer;

    class MarketDataLiveClient : public IMarketDataProvider
    {
    private:
        inline static const std::string CLASS = "MarketDataLiveClient";

        BeaconTech::Common::Logger* logger = nullptr;
        std::string clientName;
        databento::LiveBlocking client;
        std::unique_ptr<MarketDataStreamingClient<MarketDataLiveClient>> streamingClient;

    public:

        explicit MarketDataLiveClient(std::string clientName, BeaconTech::Common::Logger* logger);

        ~MarketDataLiveClient() override = default;

        void subscribe(MarketDataLiveClient& marketDataClient, const Common::MdCallback& callback);

        std::function<void ()> getBookUpdate(MarketDataProcessor& streamingProcessor) override;

        const std::string& getClientName() const;

        void stop() override;

        // Deleted default ctors and assignment operators
        MarketDataLiveClient() = delete;

        MarketDataLiveClient(const MarketDataLiveClient& other) = delete;

        MarketDataLiveClient(MarketDataLiveClient&& other) = delete;

        MarketDataLiveClient& operator=(const MarketDataLiveClient& other) = delete;

        MarketDataLiveClient operator=(MarketDataLiveClient&& other) = delete;
    };
} // namespace BeaconTech::marketdata


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP
