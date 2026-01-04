#include "marketdata/Date.hpp"
#include "curves/ZeroCurve.hpp"
#include "instruments/Cashflow.hpp"
#include "instruments/Leg.hpp"
#include "instruments/Swap.hpp"
#include "sensitivity/DV01.hpp"
#include <iostream>
#include <vector>

int main() {

    // Market values
    Date today(2026,1,1);
    std::vector<Date> dates = { Date(2027,1,1), Date(2028,1,1), Date(2029,1,1)};
    std::vector<double> rates = { 0.020, 0.0250, 0.030 };
    ZeroCurve discountCurve(today, dates, rates, DayCountConvention::ACT_360, CompoundConvention::CONTINUOUS);

    // Fixed leg flows
    std::vector<Cashflow> fixedCashflows = {
        { Date(2027, 1, 1), 20000.0 },
        { Date(2028, 1, 1), 20000.0 },
        { Date(2029, 1, 1), 20000.0 }
    };
    Leg fixedLeg(fixedCashflows);

    // Floating leg flows
    std::vector<Cashflow> floatingCashflows = {
        { Date(2026, 7, 1), 15000.0 },
        { Date(2027, 1, 1), 16000.0 },
        { Date(2027, 7, 1), 15500.0 },
        { Date(2028, 1, 1), 16500.0 },
        { Date(2028, 7, 1), 15800.0 },
        { Date(2029, 1, 1), 17000.0 }
    };
    /*
    std::vector<Cashflow> floatingCashflows = {
        { Date(2027, 1, 1), 20000.0 },
        { Date(2028, 1, 1), 20000.0 },
        { Date(2029, 1, 1), 20000.0 }
    };
    */
    Leg floatingLeg(floatingCashflows);

    // Create swap and price
    Swap swap(fixedLeg, floatingLeg);
    double npv = swap.npv(discountCurve);

    std::cout << "Swap NPV: " << npv << std::endl;

    // Compute DV01
    double bumpAmount = 0.0001;
    std::vector<double> bumpedRates;
    for (const double r : rates)
        bumpedRates.push_back(r+bumpAmount);
    ZeroCurve discountCurveBumped(today, dates, bumpedRates, DayCountConvention::ACT_360, CompoundConvention::CONTINUOUS);
    double dv01 = DV01(swap, discountCurve, discountCurveBumped);

    std::cout << "DV01: " << dv01 << std::endl;

    return 0;
}

