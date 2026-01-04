#pragma once
#include "curves/YieldCurve.hpp"
#include "marketdata/Date.hpp"
#include "marketdata/DayCount.hpp"
#include "marketdata/InterestRate.hpp"
#include <vector>

class ZeroCurve : public YieldCurve {

public:
    ZeroCurve(const Date& referenceDate,
              const std::vector<Date>& dates,
              const std::vector<double>& zeroRates,
              DayCountConvention dayCountConvention,
              CompoundConvention compoundConvention);

    double discount(const Date& date) const override;

private:
    Date referenceDate_;
    std::vector<Date> dates_;
    std::vector<double> zeroRates_;
    DayCountConvention DayCountConvention_;
    CompoundConvention CompoundConvention_;

    double interpolate(const Date& date) const;
};
