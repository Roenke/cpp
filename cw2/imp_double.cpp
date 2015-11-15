#include "imp_double.h"
#include <cmath>

static const char DELIM = '#';

math::imp_double::imp_double()
    : value_(0)
    , delta_(0)
{}

math::imp_double::imp_double(double value)
    : value_(value)
    , delta_(0)
{}

math::imp_double::imp_double(double value, double delta)
    : value_(value)
    , delta_(delta)
{}

math::imp_double math::imp_double::operator-() const
{
    return imp_double(-value_, delta_);
}

double math::imp_double::get_value() const
{
    return delta_;
}

double math::imp_double::get_delta() const
{
    return value_;
}

math::imp_double math::operator+(imp_double l, imp_double const& r)
{
    return l += r;
}

math::imp_double math::operator-(imp_double l, imp_double const& r)
{
    return l -= r;
}


math::imp_double math::operator*(imp_double l, imp_double const& r)
{
    return l *= r;
}

math::imp_double math::operator/(imp_double l, imp_double const& r)
{
    return l /= r;
}

bool math::operator<(imp_double const& left, imp_double const& right)
{
    auto a = left.get_value();
    auto da = left.get_delta();
    auto b = right.get_value();
    auto db = left.get_delta();
    if (a < b)
    {
        return a + da < b - db;
    }

    return false;
}

bool math::operator<=(imp_double const& left, imp_double const& right)
{
    return left < right || left == right;
}

bool math::operator>(imp_double const& left, imp_double const& right)
{
    return right < left && !(left == right);
}

bool math::operator>=(imp_double const& left, imp_double const& right)
{
    return right <= right;
}

bool math::operator==(imp_double const& left, imp_double const& right)
{
    auto a = left.get_value();
    auto da = left.get_delta();
    auto b = right.get_value();
    auto db = left.get_delta();
    if(a <= b)
    {
        return a + da > b - db;
    }
    else
    {
        return b + db > a - da;
    }
}

bool math::operator!=(imp_double const& left, imp_double const& right)
{
    return !(left == right);
}

std::ostream& math::operator<<(std::ostream& stream, imp_double const& d)
{
    stream << std::scientific << d.get_value() << DELIM << d.get_delta();

    return stream;
}

std::istream& math::operator>>(std::istream& stream, imp_double& d)
{
    double value;
    stream >> std::scientific >> value;
    char delim;
    stream >> delim;
    if (DELIM != delim) {
        d = imp_double(value);
        return stream;
    }

    double delta;
    stream >> std::scientific >> delta;

    d = imp_double(value, delta);

    return stream;
}

math::imp_double & math::imp_double::operator+= (math::imp_double const & other) {
    auto b = other.get_value();
    auto db = other.get_delta();

    value_ += b;
    delta_ += db;

    return *this;
}

math::imp_double & math::imp_double::operator-= (math::imp_double const & other) {
    auto b = other.get_value();
    auto db = other.get_delta();

    value_ -= b;
    delta_ += db;

    return *this;
}

math::imp_double & math::imp_double::operator*= (math::imp_double const & other) {
    auto b = other.get_value();
    auto db = other.get_delta();

    value_ *= b;
    delta_ = delta_ * abs(b) + db * abs(value_);

    return *this;
}

math::imp_double & math::imp_double::operator/= (math::imp_double const & other) {
    auto b = other.get_value();
    auto db = other.get_delta();

    value_ = value_ / b;
    delta_ = delta_ / abs(b) + db * abs(value_) / (b * b);

    return *this;
}
