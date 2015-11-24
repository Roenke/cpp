#include "lint.h"
#include <sstream>
#include <string>
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
    if(str_length < 10 || s[0] == '-' && str_length == 10)
    {
        sign_ = atoi(s.c_str());
        return;
    }

    sign_ = 1;
    bits_ = new vector<uint32_t>();
    auto start_value = static_cast<int>(s.length());
    if(s[0] == '-')
    {
        sign_ = -1;
    }

    int pasre_result;
    for (auto i = start_value; i >= 0; i -= 9)
    {
        pasre_result = atoi(i < 9 ? s.substr(0, i).c_str() : s.substr(i - 9, 9).c_str());
        if (pasre_result < 0) pasre_result *= -1;
        bits_->push_back(pasre_result);
    }

    while (bits_->size() > 1 && bits_->back() == 0) (void)bits_->pop_back();
}

lint::lint(int number)
    : sign_(number)
    , bits_(nullptr)
{}

lint::lint(long long number)
    : sign_(0)
    , bits_(nullptr)
{
    if(number > 0 && number <= static_cast<long long>(INT32_MAX) ||
        number < 0 && number >= static_cast<long long>(INT32_MIN))
    {
        sign_ = static_cast<int>(number);
    }
    else
    {
        sign_ = number > 0 ? 1 : -1;
        bits_ = new vector<uint32_t>(2);
        (*bits_)[0] = number % base;
        (*bits_)[1] = number / base;
    }
}

lint::lint(double number)
    : lint(std::to_string(number).substr(std::to_string(number).find('.')))
{}

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

lint::operator long long() const
{
    if(bits_ != nullptr)
    {
        if(bits_->size() > 1)
        {
            return static_cast<long long>((*bits_)[0]) + base * (*bits_)[1];
        }
        
        return (*bits_)[0];
    }

    return sign_;
}

lint& lint::operator=(lint const& from)
{
    return *this;
}

lint lint::operator+() const
{
    auto other(*this);
    return other;
}

lint lint::operator-() const
{
    auto other(*this);
    other.sign_ = -other.sign_;
    return other;
}

bool lint::is_small() const
{
    return bits_ == nullptr;
}

std::string lint::to_string() const
{
    if (bits_ == nullptr)
    {
        return std::to_string(sign_);
    }

    char buf[11];
    std::ostringstream ost;
    if (sign_ == -1) ost << '-';
    auto size = bits_->size();
    sprintf_s(buf, "%u", (*bits_)[static_cast<int>(size - 1)]);
    ost << buf;

    for (auto i = static_cast<int>(size - 2); i >= 0; --i)
    {
        sprintf_s(buf, "%09u", (*bits_)[i]);
        ost << buf;
    }

    return ost.str();
}

void lint::assert_optimization() const
{
    // Проверка, что число не может быть представлено как короткое
    if(bits_ == nullptr)
    {
        return;
    }
    for (int i = bits_->size() - 1; i > 0; --i)
    {
        if ((*bits_)[i] != 0)
        {
            return;
        }
    }

    assert(false);
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
    
    if(l.bits_ == nullptr || r.bits_ == nullptr)
    {
        return false;
    }

    auto& lbits = *l.bits_;
    auto& rbits = *r.bits_;

    int i;
    auto min_size = std::min(lbits.size(), rbits.size());
    for (i = 0; i < min_size; ++i)
    {
        if (lbits[i] != rbits[i])
        {
            return false;
        }
    }

    for (auto j = i; j < rbits.size(); ++j)
    {
        if(rbits[j] != 0)
        {
            return false;
        }
    }

    for (auto j = i; j < lbits.size(); ++j)
    {
        if(lbits[j] != 0)
        {
            return false;
        }
    }

    return true;
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
