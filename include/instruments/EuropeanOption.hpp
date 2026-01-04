#pragma once

enum class OptionType {
    CALL,
    PUT
};

class EuropeanOption {

public:
    EuropeanOption(
        OptionType type,
        double strike,
        double maturity
    );

    OptionType type() const;
    double strike() const;
    double maturity() const;
    double payoff(double stockPrice) const;

private:
    OptionType type_;
    double strike_;
    double maturity_;

};
