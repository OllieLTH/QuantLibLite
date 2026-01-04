#include "marketdata/InterestRate.hpp"
#include <cmath>

double discountFactor(double rate,
                      double t,
                      CompoundConvention compoundConvention)
{
    switch (compoundConvention) {
        case CompoundConvention::CONTINUOUS:
            return std::exp(-rate * t);

        case CompoundConvention::ANNUAL:
            return 1.0 / std::pow(1 + rate, t);

        case CompoundConvention::SEMIANNUAL:
            return 1.0 / std::pow(1 + rate/2.0, 2*t);

        default: // Use continuous as default
            return std::exp(-rate * t);
    }
}
