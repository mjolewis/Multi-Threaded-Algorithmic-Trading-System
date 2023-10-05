# Multi-Threaded-Algorithmic-Trading-System
An event-based algorithmic trading system, with plug-n-play strategies for live trading and backtesting infrastructure

# Libraries
1. **<ins>Market Data<ins>**  
   1. Provider: Databento  
   2. Purpose: Provides low-latency live and historical market data without data loss. Typical normalization is 
      6.1-microsecond with practically zero data gaps with their FPGA-based capture.  
   3. Setup: You need an API key to request for data from Databento. Sign up and you will automatically receive a 
   set of API keys to start with. Each API key is a 32-character string starting with db-, that can be found from 
   the API Key page on your portal.  
   4. Pricing: Base license fees charged by the venue for live data and passed through directly as-is. 
Billed in advance each month and not prorated.  
   5. https://docs.databento.com/pricing-guide  
   6. https://databento.com/pricing  
   7. Getting Started: https://docs.databento.com/getting-started?historical=python&live=python  
2. **<ins>JSON<ins>**  
   1. Provider: nlohmann/json  
   2. Purpose: Parse JSON formatted configuration files  
   3. Getting Started: https://github.com/nlohmann/json