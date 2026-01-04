#include "models/BlackScholes.hpp"
#include "instruments/EuropeanOption.hpp"
#include "marketdata/EquityMarketData.hpp"
#include "mathengines/EngineFD.hpp"
#include <iostream>

int main() {
    // Option data
    EuropeanOption option(
        OptionType::CALL,
        100.0,   // strike
        1.0      // maturity (1 year)
    );

    // Market data
    EquityMarketData market(
        100.0,   // spot
        0.05,    // rate
        0.20     // volatility
    );

    // Black scholes model and price
    BlackScholes model;

    double price = model.price(option, market);
    std::cout << "Black-Scholes Price: " << price << std::endl << std::endl;

    // Greeks (Analytic)
    double delta = model.delta(option, market);
    double vega  = model.vega(option, market);
    double rho = model.rho(option, market);
    double theta  = model.theta(option, market);

    std::cout << "_Analytic Greeks_" << std::endl;
    std::cout << "Delta: " << delta << std::endl;
    std::cout << "Vega: " << vega << std::endl;
    std::cout << "Rho: " << rho << std::endl;
    std::cout << "Theta: " << theta << std::endl << std::endl;

    // Greeks (Finite Differences)
    double deltaFD = FiniteDifference::derivative(
        [&](double S) {
            EquityMarketData bumpedMarket(
                S,
                market.rate(),
                market.volatility()
            );
            return model.price(option, bumpedMarket);
        },
        market.spot(),
        1e-4
    );
    double vegaFD = FiniteDifference::derivative(
        [&](double vol) {
            EquityMarketData bumpedMarket(
                market.spot(),
                market.rate(),
                vol
            );
            return model.price(option, bumpedMarket);
        },
        market.volatility(),
        1e-4
    );
    double rhoFD = FiniteDifference::derivative(
        [&](double r) {
            EquityMarketData bumpedMarket(
                market.spot(),
                r,
                market.volatility()
            );
            return model.price(option, bumpedMarket);
        },
        market.rate(),
        1e-4
    );
    double thetaFD = FiniteDifference::derivative(
        [&](double dt) {
            double newMaturity = option.maturity() - dt;
            if (newMaturity <= 0.0) return 0.0;

            EuropeanOption bumpedOption(
                option.type(),
                option.strike(),
                newMaturity
            );
            return model.price(bumpedOption, market);
        },
        0.0,
        1.0 / 250.0,
        FDType::FORWARD
    );
    std::cout << "_Finite Difference Greeks_" << std::endl;
    std::cout << "Delta: " << deltaFD << std::endl;
    std::cout << "Vega: " << vegaFD << std::endl;
    std::cout << "Rho: " << rhoFD << std::endl;
    std::cout << "Theta: " << thetaFD << std::endl;

    return 0;
}
