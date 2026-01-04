#pragma once
#include "Cashflow.hpp"
#include <vector>

class Leg {
    
public:
    Leg() = default;
    Leg(const std::vector<Cashflow>& cashflows) 
        : cashflows_(cashflows) {}

    void addCashflow(const Cashflow& cf) { cashflows_.push_back(cf); }
    const std::vector<Cashflow>& cashflows() const { return cashflows_; }

private:
    std::vector<Cashflow> cashflows_;
    
};

