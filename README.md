# Contents
- [Beacon Tech](#beacon-tech)
- [Components](#components)
- [System Architecture](#system-architecture)
- [External Libraries](#external-libraries)
- [Environment Specifications](#environment-specifications)
- [About Me](#about-me)
- [Contact Info](#contact-info)

# Beacon Tech
**Beacon Tech** is a cutting-edge high-frequency trading system that supports market-making and liquidity-taking 
strategies. Built with modern C++, it deterministically sequences order book updates into downstream load-balanced 
and lock-free components that manage orders, positions, risk (and more) while emitting orders to exchanges around the world.

# Components
- Exchange Simulator 
  - Order Gateway Server 
  - Matching Engine 
  - Market Data Publisher 
- Feed Handlers 
- Order Book Builder 
- Strategies 
- Order Manager (In Development)
- Position Manager (Scoping)
- Risk Manager (Backlog)

# System Architecture

# External Libraries
- **<ins>Market Data<ins>**
  - Provider: Databento
  - Purpose: Provides low-latency live and historical market data without data loss. Typical normalization is 
  6.1-microsecond with practically zero data gaps with their FPGA-based capture.
  - Setup: You need an API key to request for data from Databento. Sign up and you will automatically receive a 
  set of API keys to start with. Each API key is a 32-character string starting with db-, that can be found from 
  the API Key page on your portal. 
  - Pricing: Base license fees charged by the venue for live data and passed through directly as-is. 
    Billed in advance each month and not prorated.
    - https://docs.databento.com/pricing-guide
    - https://databento.com/pricing
  - Getting Started: https://docs.databento.com/getting-started?historical=python&live=python  
- **<ins>JSON<ins>**
  - Provider: nlohmann/json   
  - Purpose: Parse JSON formatted configuration files (configuration settings will eventually be persisted to a database and loaded into memory at startup)
  - Getting Started: https://github.com/nlohmann/json

# Environment Specifications
- C++: Language version 20 (ISO/IEC 14882:2020)
- Clang: Apple clang version 14.0.3 (clang-1403.0.22.14.1)
- CMake: cmake version 3.26.4 
- Ninja: 1.11.1

# About Me
I’ve been working in finance since 2008 and building high-frequency trading software since 2019. Primarily using C++ 
or Java (via the sequencer framework) for the core system.

I am a software engineer with a deep passion for algorithmic trading and have extensive experience in building 
end-to-end high-frequency trading systems. Throughout my experience, I have developed a thorough understanding of the 
technical challenges and complex market dynamics faced by today's most advanced organizations. As a result, I am able
to add immediate impact and help firms grow revenues while streaming costs.

My journey in electronic trading began at a algorithmic trading firm, where I developed and optimized high-frequency 
trading and order management systems for cash equities and equity swaps. This experience gave me a firsthand look at 
the exciting world of today's markets and lead to the creation of Beacon Tech.

In addition to my work in electronic trading, I am a life-long learner who always stays at the cutting edge of new 
language features and technologies. This discipline allows me to distill modern approaches to complex problems that 
can be used to advance any organizations strategic objectives.

Through Beacon Tech, I hope to showcase my skill set by building a production quality system.

# Contact Info
For any recruiters interesting in connecting, please use my LinkedIn profile. [LinkedIn](https://www.linkedin.com/in/mjolewis/)