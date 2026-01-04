#include "marketdata/DayCount.hpp"

const double yearFraction(const Date& startDate,
                    const Date& endDate,
                    const DayCountConvention dayCountConvention)
{
    double days = endDate.daysSinceEpoch() - startDate.daysSinceEpoch();

    switch(dayCountConvention) {
        case DayCountConvention::ACT_360:
            return days / 360.0;

        case DayCountConvention::ACT_365:
            return days / 365.0;

        default: // Use ACT_365 as default
            return days / 365.0;

    }
}
