#include "marketdata/DayCount.hpp"
#include "marketdata/InterestRate.hpp"
#include "curves/ZeroCurve.hpp"
#include <iostream>

int main() {
    Date today(2026,1,1);
    std::vector<Date> dates = { Date(2027,1,1), Date(2028,1,1) };
    std::vector<double> rates = { 0.02, 0.04 };
    ZeroCurve curve(today, dates, rates, DayCountConvention::ACT_360, CompoundConvention::CONTINUOUS);

    std::cout << "Discount factor (pre-curve): "
              << curve.discount(Date(2026,6,1)) << std::endl;

    std::cout << "Discount factor (first date): "
              << curve.discount(Date(2027,1,1)) << std::endl;
              
    std::cout << "Discount factor (interpolation): "
              << curve.discount(Date(2027,6,1)) << std::endl;
    
    std::cout << "Discount factor (last date): "
              << curve.discount(Date(2028,1,1)) << std::endl;

    std::cout << "Discount factor (post-curve): "
              << curve.discount(Date(2028,6,1)) << std::endl;

    return 0;
}
