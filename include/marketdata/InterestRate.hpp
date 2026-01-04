#pragma once

enum class CompoundConvention {
    CONTINUOUS,
    ANNUAL,
    SEMIANNUAL
};

double discountFactor(double rate,
                      double t,
                      CompoundConvention compoundConvention);
                      
