#include "models/BlackScholes.hpp"
#include <cmath>

namespace {
    double normalCDF(double x) {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }

    double normalPDF(double x) {
        static const double invSqrt2Pi = 0.3989422804014327;
        return invSqrt2Pi * std::exp(-0.5 * x * x);
    }
}

double BlackScholes::price(
    const EuropeanOption& option,
    const EquityMarketData& market
) const {
    double S = market.spot();
    double K = option.strike();
    double r = market.rate();
    double sigma = market.volatility();
    double T = option.maturity();

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T)
              / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (option.type() == OptionType::CALL) {
        return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
    } else if (option.type() == OptionType::PUT) {
        return K * std::exp(-r * T) * normalCDF(-d2)
             - S * normalCDF(-d1);
    } else {
        // Default to call
        return S * normalCDF(d1) - K * std::exp(-r * T) * normalCDF(d2);
    }
}

double BlackScholes::delta(
    const EuropeanOption& option,
    const EquityMarketData& market
) const {
    double S = market.spot();
    double K = option.strike();
    double r = market.rate();
    double sigma = market.volatility();
    double T = option.maturity();

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T)
              / (sigma * std::sqrt(T));

    if (option.type() == OptionType::CALL) {
        return normalCDF(d1);
    } else if (option.type() == OptionType::PUT) {
        return normalCDF(d1) - 1.0;
    } else {
        // Default to call
        return normalCDF(d1);
    }
}

double BlackScholes::vega(
    const EuropeanOption& option,
    const EquityMarketData& market
) const {
    double S = market.spot();
    double K = option.strike();
    double r = market.rate();
    double sigma = market.volatility();
    double T = option.maturity();

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T)
              / (sigma * std::sqrt(T));

    return S * std::sqrt(T) * normalPDF(d1);
}

double BlackScholes::theta(
    const EuropeanOption& option,
    const EquityMarketData& market
) const {
    double S = market.spot();
    double K = option.strike();
    double r = market.rate();
    double sigma = market.volatility();
    double T = option.maturity();

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T)
              / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    double firstTerm = - (S * normalPDF(d1) * sigma)
                        / (2.0 * std::sqrt(T));

    if (option.type() == OptionType::CALL) {
        return firstTerm
             - r * K * std::exp(-r * T) * normalCDF(d2);
    } else if (option.type() == OptionType::PUT) {
        return firstTerm
             + r * K * std::exp(-r * T) * normalCDF(-d2);
    } else {
        // Default to call
        return firstTerm
             - r * K * std::exp(-r * T) * normalCDF(d2);
    }
}

double BlackScholes::rho(
    const EuropeanOption& option,
    const EquityMarketData& market
) const {
    double K = option.strike();
    double r = market.rate();
    double T = option.maturity();

    double S = market.spot();
    double sigma = market.volatility();

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T)
              / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (option.type() == OptionType::CALL) {
        return K * T * std::exp(-r * T) * normalCDF(d2);
    } else if (option.type() == OptionType::PUT) {
        return -K * T * std::exp(-r * T) * normalCDF(-d2);
    } else {
        // Default to call
        return K * T * std::exp(-r * T) * normalCDF(d2);
    }
}

