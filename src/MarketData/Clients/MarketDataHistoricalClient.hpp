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
        std::string clientName;
        std::shared_ptr<databento::Historical> client;
        std::shared_ptr<MarketDataStreamingClient<MarketDataHistoricalClient>> streamingClient;

    public:
        explicit MarketDataHistoricalClient(std::string clientName);
        ~MarketDataHistoricalClient() override;

        const std::string& getClientName() const;
        std::shared_ptr<IMarketDataProvider> getClient() const override;
        static std::vector<std::string> doBatchDownload(const std::shared_ptr<databento::Historical>& _client);
        static std::vector<std::string> readFromFile();
        std::function<void ()> getBookUpdate() const override;
        void stop();
    };
}


#endif //MULTI_THREADED_ALGORITHMIC_TRADING_SYSTEM_MARKETDATAHISTORICALCLIENT_HPP