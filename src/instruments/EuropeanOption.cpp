#include "instruments/EuropeanOption.hpp"
#include <algorithm>

EuropeanOption::EuropeanOption(
    OptionType type,
    double strike,
    double maturity
)
    : type_(type), strike_(strike), maturity_(maturity) {}

OptionType EuropeanOption::type() const { return type_; }
double EuropeanOption::strike() const { return strike_; }
double EuropeanOption::maturity() const { return maturity_; }
double EuropeanOption::payoff(double stockPrice) const { 
    if (type_ == OptionType::CALL) {
        return (stockPrice - strike_) > 0 ? (stockPrice - strike_) : 0;
    } else if (type_ == OptionType::PUT) {
        return (strike_ - stockPrice) > 0 ? (strike_ - stockPrice) : 0;
    } else {
        // Default to Call
        return (stockPrice - strike_) > 0 ? (stockPrice - strike_) : 0;
    }

}
