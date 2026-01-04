#pragma once
#include "Leg.hpp"
#include "curves/YieldCurve.hpp"
#include "marketdata/InterestRate.hpp"


class Swap {
    
public:
    Swap(Leg fixed, Leg floating)
        : fixed_(fixed), floating_(floating) {}

    double npv(const YieldCurve& discountCurve) const;

    const Leg& fixed() const { return fixed_; }
    const Leg& floating() const { return floating_; }

private:
    Leg fixed_;
    Leg floating_;
    
};

