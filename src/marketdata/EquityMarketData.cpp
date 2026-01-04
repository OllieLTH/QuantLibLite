#include "marketdata/EquityMarketData.hpp"

EquityMarketData::EquityMarketData(
    double spot,
    double rate,
    double volatility
)
    : spot_(spot), rate_(rate), volatility_(volatility) {}

double EquityMarketData::spot() const { return spot_; }
double EquityMarketData::rate() const { return rate_; }
double EquityMarketData::volatility() const { return volatility_; }

