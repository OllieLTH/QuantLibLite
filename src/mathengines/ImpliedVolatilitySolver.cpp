#include "mathengines/ImpliedVolatilitySolver.hpp"
#include <cmath>

double ImpliedVolatilitySolver::solve(
    const EuropeanOption& option,
    const EquityMarketData& market,
    double marketPrice,
    double initialGuess
) const {
    double sigma = initialGuess;
    double price = 0.0;
    double vega = 0.0;

    for (int i = 0; i < maxIter_; i++) {
        // Create market with current sigma
        EquityMarketData bumpedMarket(
            market.spot(),
            market.rate(),
            sigma
        );

        price = model_.price(option, bumpedMarket);
        vega  = model_.vega(option, bumpedMarket);

        double diff = price - marketPrice;

        if (std::abs(diff) < tol_) {
            return sigma; // converged
        }

        if (vega < 1e-8) { // avoid division by tiny Vega
            break; // fallback could go here
        }

        sigma -= diff / vega; // Newton-Raphson update
    }

    // fallback: simple bisection
    double lower = 1e-6;
    double upper = 1e2;
    sigma = initialGuess;

    for (int i = 0; i < maxIter_; i++) {
        EquityMarketData bumpedMarket(
            market.spot(),
            market.rate(),
            sigma
        );
        price = model_.price(option, bumpedMarket);

        if (std::abs(price - marketPrice) < tol_) return sigma;

        if (price < marketPrice)
            lower = sigma;
        else
            upper = sigma;

        sigma = 0.5 * (lower + upper);
    }

    return -1;

}

