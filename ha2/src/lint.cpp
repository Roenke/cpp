#include "lint.h"
#include <algorithm>
using namespace apa;
using helpers::vector;
lint::lint()
    : sign_(0)
    , bits_(nullptr)
{
}

// stub
lint::lint(std::string const& s)
    : sign_(0)
    , bits_(nullptr)
{
    auto str_length = s.length();
    if(str_length < 9 || s[0] == '-' && str_length == 9)
    {
        sign_ = atoi(s.c_str());
        return;
    }

    bits_ = new vector<uint32_t>();
    auto start_value = static_cast<int>(s.length());
    int pasre_result;
    for (auto i = start_value; i > 0; i -= 9)
    {
        pasre_result = atoi(i < 9 ? s.substr(0, i).c_str() : s.substr(i - 9, 9).c_str());
        bits_->push_back(pasre_result);
    }
    while (bits_->size() > 1 && bits_->back() == 0) (void)bits_->pop_back();
}

lint::lint(int number)
    : sign_(number)
    , bits_(nullptr)
{}

lint::lint(long long number)
    : sign_(number)
    , bits_(nullptr)
{}

//stub
lint::lint(double)
    : bits_(nullptr)
{
    sign_ = 0;
}

lint::lint(lint const& other)
    : sign_(other.sign_)
    , bits_(nullptr)
{
    if(other.bits_ != nullptr)
    {
        bits_ = new vector<uint32_t>(*other.bits_);
    }
}

lint::operator bool() const
{
    return sign_ != 0;
}

lint::operator int() const
{
    if(bits_ == nullptr)
    {
        return sign_;
    }

    return (*bits_)[0];
}

lint::operator long() const
{
    return 0L;
}

lint& lint::operator=(lint const& from)
{
    return *this;
}

lint& lint::operator+()
{
    sign_ = 0;
    return *this;
}

lint& lint::operator-()
{
    sign_ = 1;
    return *this;
}

std::string lint::to_string() const
{
    return "";
}

lint& apa::operator++(lint& val)
{
    return val += 1;
}

lint apa::operator++(lint& val, int)
{
    auto old_value(val);
    val += 1;
    return old_value;
}

lint& apa::operator--(lint& value)
{
    return value -= 1;
}

lint apa::operator--(lint& value, int)
{
    auto old_value(value);

    value += 1;
    return old_value;
}

bool apa::operator==(lint const& l, lint const& r)
{
    if (l.sign_ != r.sign_)
    {
        return false;
    }
    if(l.bits_ == nullptr && r.bits_ == nullptr)
    {
        return true;
    }
    
    return l.bits_ == r.bits_;
}

bool apa::operator!=(lint const& l, lint const& r)
{
    return !(l == r);
}

// stub
bool apa::operator<(lint const& l, lint const& r)
{
    if(l.bits_ == nullptr && r.bits_ == nullptr)
    {
        return l.sign_ < r.sign_;
    }

    return false;
}

bool apa::operator>(lint const& l, lint const& r)
{
    return r < l;
}

bool apa::operator>=(lint const& l, lint const& r)
{
    return !(r > l);
}

bool apa::operator<=(lint const& l, lint const& r)
{
    return !(l > r);
}

lint& apa::operator+=(lint& l, lint const&r)
{
    // stub. Todo: implement

    return l;
}

lint& apa::operator-=(lint& l, lint const&r)
{
    // stub. Todo: implement
    return l;
}

lint& apa::operator*=(lint& l, lint const&r)
{
    // stub. Todo: implement
    return l;
}

lint& apa::operator/=(lint& l, lint const& r)
{
    // stub. Todo: implement
    return l;
}

lint apa::operator+(lint l, lint const& r)
{
    return l += r;
}

lint apa::operator-(lint l, lint const& r)
{
    return l -= r;
}

lint apa::operator*(lint l, lint const& r)
{
    return l *= r;
}

lint apa::operator/(lint l, lint const&r)
{
    return l /= r;
}

std::ostream& apa::operator<<(std::ostream& stream, lint const& d)
{
    return stream;
}

std::istream& apa::operator>>(std::istream& stream, lint& d)
{
    return stream;
}

lint apa::abs(lint& other)
{
    return other > 0 ? other : -other;
}

lint apa::pow(lint&, int)
{
    // stub. ToDo: implement O(log(n)) pow
    return 0;
}
