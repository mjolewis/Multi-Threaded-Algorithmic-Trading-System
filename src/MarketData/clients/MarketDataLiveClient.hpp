//
// Connects to a market data provider using a subscription style protocol. This client
// communicates with the providers real-time data gateway using the C++ API.
//
// Created by Michael Lewis on 9/29/23.
//

#ifndef MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP
#define MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP

#include <functional>
#include <memory>
#include <string>

#include <databento/live.hpp>
#include <databento/log.hpp>

#include "IMarketDataProvider.hpp"
#include "MarketDataStreamingClient.hpp"
#include "CommonServer/TypeSystem/MdTypes.hpp"

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
        std::string clientName;
        std::shared_ptr<databento::LiveBlocking> client;
        std::shared_ptr<MarketDataStreamingClient<MarketDataLiveClient>> streamingClient;

    public:
        MarketDataLiveClient() = default;

        explicit MarketDataLiveClient(std::string clientName);

        ~MarketDataLiveClient() override = default;

        void subscribe(std::shared_ptr<MarketDataLiveClient> marketDataClient, const Common::MdCallback& callback);

        std::function<void ()> getBookUpdate(std::shared_ptr<MarketDataProcessor>& streamingProcessor) override;

        const std::string& getClientName() const;

        void stop() override;

        // Deleted default ctors and assignment operators
        MarketDataLiveClient(const MarketDataLiveClient& other) = delete;

        MarketDataLiveClient(MarketDataLiveClient&& other) = delete;

        MarketDataLiveClient& operator=(const MarketDataLiveClient& other) = delete;

        MarketDataLiveClient operator=(MarketDataLiveClient&& other) = delete;
    };
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP
