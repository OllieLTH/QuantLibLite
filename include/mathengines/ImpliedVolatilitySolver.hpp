#pragma once
#include "instruments/EuropeanOption.hpp"
#include "marketdata/EquityMarketData.hpp"
#include "models/BlackScholes.hpp"

class ImpliedVolatilitySolver {
public:
    ImpliedVolatilitySolver(
        const BlackScholes& model,
        double tol = 1e-6,
        int maxIter = 100
    ) : model_(model), tol_(tol), maxIter_(maxIter) {}

    double solve(
        const EuropeanOption& option,
        const EquityMarketData& market,
        double marketPrice,
        double initialGuess
    ) const;

private:
    const BlackScholes& model_;
    double tol_;
    int maxIter_;
};
