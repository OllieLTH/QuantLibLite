#pragma once
#include "marketdata/Date.hpp"

struct Cashflow {
    Date paymentDate;
    double paymentValue;

    Cashflow(const Date& date, double value) 
        : paymentDate(date), paymentValue(value) {}
};

