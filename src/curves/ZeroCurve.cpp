#include "curves/ZeroCurve.hpp"

ZeroCurve::ZeroCurve(const Date& referenceDate,
                     const std::vector<Date>& dates,
                     const std::vector<double>& zeroRates,
                     DayCountConvention dayCountConvention,
					 CompoundConvention compoundConvention)
    : referenceDate_(referenceDate),
      dates_(dates),
      zeroRates_(zeroRates),
      DayCountConvention_(dayCountConvention),
	  CompoundConvention_(compoundConvention) {}

double ZeroCurve::discount(const Date& date) const {
    double t = yearFraction(referenceDate_, date, DayCountConvention_);
    double r = interpolate(date);
	return discountFactor(r, t, CompoundConvention_);
}

double ZeroCurve::interpolate(const Date& date) const {

	if (date <= dates_.front()) {
		return zeroRates_.front();

	} else if (date >= dates_.back()) {
		return zeroRates_.back();

	} else {

		// Iterate through vector
		for (int i = 1; i < dates_.size(); i++) {

			if (date == dates_[i]) {
				return zeroRates_[i];

			} else if ((date > dates_[i-1]) && (date < dates_[i])) {
				double t1 = yearFraction(referenceDate_, dates_[i-1], DayCountConvention_);
				double t2 = yearFraction(referenceDate_, dates_[i], DayCountConvention_);
				double t  = yearFraction(referenceDate_, date, DayCountConvention_);

				double r1 = zeroRates_[i-1];
				double r2 = zeroRates_[i];

				// Linear interpolation
				return r1 + (r2 - r1) * (t - t1) / (t2 - t1);
			}
    	}
		
	}

	// As fall-back use final rate (shouldn't reach this point)
	return zeroRates_.back();

};

