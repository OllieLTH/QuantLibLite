#include "models/BlackScholes.hpp"
#include "mathengines/ImpliedVolatilitySolver.hpp"
#include "marketdata/EquityMarketData.hpp"
#include <iostream>

int main() {

    // Option data
    EuropeanOption option(
        OptionType::CALL,
        100.0,   // strike
        1.0      // maturity (1 year)
    );

    // Market data
    double actualVol = 0.20;
    EquityMarketData market(
        100.0,   // spot
        0.05,    // rate
        actualVol     // volatility
    );

    // Black scholes model and price
    BlackScholes model;
    double marketPrice = model.price(option, market);

    // Use price to estimate the market-implied
    ImpliedVolatilitySolver solver(model);
    double initialGuess = 0.15;
    double impliedVol = solver.solve(option, market, marketPrice, initialGuess);

    std::cout << "Actual vol: " << actualVol << "\n";
    std::cout << "Solved implied vol: " << impliedVol << "\n";

    return 0;
}
