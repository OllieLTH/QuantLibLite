#include "instruments/Swap.hpp"
#include <cmath>

double Swap::npv(const YieldCurve& discountCurve) const {
    double pvFixed = 0.0;
    for (const auto& cf : fixed_.cashflows())
        pvFixed += cf.paymentValue * discountCurve.discount(cf.paymentDate);

    double pvFloating = 0.0;
    for (const auto& cf : floating_.cashflows())
        pvFloating += cf.paymentValue * discountCurve.discount(cf.paymentDate);

    return pvFloating - pvFixed;  // NPV from payer perspective
}

