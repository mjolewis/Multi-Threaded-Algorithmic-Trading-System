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
        ~MarketDataLiveClient() override;

        const std::string& getClientName() const;

        std::shared_ptr<IMarketDataProvider> getClient() const override;

        std::function<void ()> getBookUpdate(MarketDataProcessor& streamingProcessor) override;

        void stop();
    };
} // namespace BeaconTech::MarketData


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATALIVECLIENT_HPP
