#include "mathengines/EngineFD.hpp"

double FiniteDifference::derivative(
    const std::function<double(double)>& f,
    double x,
    double h,
    FDType type
) {
    switch (type) {
        case FDType::FORWARD:
            return (f(x + h) - f(x)) / h;

        case FDType::BACKWARD:
            return (f(x) - f(x - h)) / h;

        case FDType::CENTRAL:
            return (f(x + h) - f(x - h)) / (2.0 * h);

        default:
            // Default to central
            return (f(x + h) - f(x - h)) / (2.0 * h);
    }
}

