#pragma once

#include <functional>

enum class FDType {
    FORWARD,
    BACKWARD,
    CENTRAL
};

class FiniteDifference {
public:
    static double derivative(
        const std::function<double(double)>& f,
        double x,
        double h,
        FDType type = FDType::CENTRAL
    );
};
