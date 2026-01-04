#pragma once
#include "curves/YieldCurve.hpp"
#include "instruments/Swap.hpp"

double DV01(
    const Swap& swap,
    const YieldCurve& baseCurve,
    const YieldCurve& bumpedCurve
);