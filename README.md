# Multi-Threaded-Algorithmic-Trading-System
A low-latency, event-based algorithmic trading system, with plug and play strategies. The system supports 
both live trading and backtesting infrastructure.

# Contents
1. [Introduction](#introduction)
2. [Components](#components)
2. [System Architecture](#system-architecture)
3. [External Libraries](#external-libraries)
4. [Environment Specifications](#environment-specifications)

# Introduction
A high performance, multi-threaded trading system that supports any number of customizable strategies. 
The system directly consumes multicast market-data from a low-latency market data provider and deterministically 
sequences the update events into downstream, lock-free components. Additionally, these update events are partitioned and 
scheduled onto distinct threads based on the instrument id as a way to optimize tick-to-order latency, which 
is a critical metric for HFT systems. 

In summary, the system handles market data feeds internally, makes a trade decision, and emits an order 
using a binary protocol (order submission is currently under development).

# Components
1. Feed Handlers
2. Order Book Builder
3. Strategies
4. Order Manager (In Development)
5. Position Manager (Scoping)
6. Risk Manager (Backlog)

# System Architecture

# External Libraries
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
   2. Purpose: Parse JSON formatted configuration files (configuration settings will eventually be persisted to a database and loaded into memory at startup) 
   3. Getting Started: https://github.com/nlohmann/json

# Environment Specifications
1. C++: Language version 20 (ISO/IEC 14882:2020)
2. Clang: Apple clang version 14.0.3 (clang-1403.0.22.14.1)
2. CMake: cmake version 3.26.4
3. Ninja: 1.11.1