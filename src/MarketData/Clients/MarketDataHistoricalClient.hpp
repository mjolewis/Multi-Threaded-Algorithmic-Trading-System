//
// Created by Michael Lewis on 9/26/23.
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
#include "MarketDataStreamingClient.hpp"

namespace MarketData
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
        std::shared_ptr<databento::Historical> client;
        std::shared_ptr<MarketDataStreamingClient<MarketDataHistoricalClient>> streamingClient;

    public:
        MarketDataHistoricalClient();
        ~MarketDataHistoricalClient() override = default;

        // Static Functions
        static std::vector<std::string> readFromFile();

        // Function Overrides
        std::shared_ptr<IMarketDataProvider> getClient() const override;
        std::vector<std::string> doBatchDownload(std::shared_ptr<databento::Historical>& _client) const;
        std::function<void ()> getBookUpdate() const override;
        void stop() override;
    };
}


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP
