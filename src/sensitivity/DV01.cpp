#include "sensitivity/DV01.hpp"

double DV01(
    const Swap& swap,
    const YieldCurve& baseCurve,
    const YieldCurve& bumpedCurve
) {
    return swap.npv(bumpedCurve) - swap.npv(baseCurve);
};
