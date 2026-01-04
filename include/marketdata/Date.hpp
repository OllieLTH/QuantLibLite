#pragma once

class Date {

public:
    Date(int y, int m, int d);

    int year() const;
    int month() const;
    int day() const;

    bool operator<(const Date& otherDate) const;
    bool operator<=(const Date& otherDate) const;
    bool operator>(const Date& otherDate) const;
    bool operator>=(const Date& otherDate) const;
    bool operator==(const Date& otherDate) const;

    int daysSinceEpoch() const;

private:
    int year_, month_, day_;

};
