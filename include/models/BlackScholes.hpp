#pragma once
#include "instruments/EuropeanOption.hpp"
#include "marketdata/EquityMarketData.hpp"

class BlackScholes {
public:
    double price(
        const EuropeanOption& option,
        const EquityMarketData& equityMarketData
    ) const;

    double delta(
        const EuropeanOption& option,
        const EquityMarketData& equityMarketData
    ) const;

    double vega(
        const EuropeanOption& option,
        const EquityMarketData& equityMarketData
    ) const;

    double rho(
        const EuropeanOption& option,
        const EquityMarketData& equityMarketData
    ) const;

    double theta(
        const EuropeanOption& option,
        const EquityMarketData& equityMarketData
    ) const;
};
