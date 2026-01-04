#pragma once
#include "marketdata/Date.hpp"
#include "marketdata/InterestRate.hpp"

class YieldCurve {

public:

    virtual double discount(const Date& d) const = 0;
};