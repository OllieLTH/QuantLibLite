# include "marketdata/Date.hpp"

Date::Date(int y, int m, int d) : year_(y), month_(m), day_(d) {}

int Date::year() const { return year_; }
int Date::month() const { return month_; }
int Date::day() const { return day_; }

int Date::daysSinceEpoch() const {
    // Todo: Extend to make properly consistent
    return year_ * 365 + month_ * 30 + day_;
}

bool Date::operator<(const Date& otherDate) const {
    return daysSinceEpoch() < otherDate.daysSinceEpoch();
}

bool Date::operator<=(const Date& otherDate) const {
    return daysSinceEpoch() <= otherDate.daysSinceEpoch();
}

bool Date::operator>(const Date& otherDate) const {
    return daysSinceEpoch() > otherDate.daysSinceEpoch();
}

bool Date::operator>=(const Date& otherDate) const {
    return daysSinceEpoch() >= otherDate.daysSinceEpoch();
}

bool Date::operator==(const Date& otherDate) const {
    return daysSinceEpoch()== otherDate.daysSinceEpoch();
}
