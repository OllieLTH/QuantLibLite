#pragma once
#include "marketdata/Date.hpp"

enum class DayCountConvention {
    ACT_360,
    ACT_365
};

const double yearFraction(const Date& start,
                    const Date& end,
                    const DayCountConvention dayCountConvention);
