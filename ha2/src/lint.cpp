#include "lint.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace apa;
using helpers::vector;
lint::lint()
    : sign_(0)
    , bits_(nullptr)
{
}

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
    from_long_long(number);
}

lint::lint(double number)
    : lint(std::to_string(number).substr(0, std::to_string(number).find('.')))
{}

lint::~lint()
{
    if(bits_ != nullptr)
    {
        delete bits_;
    }
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

lint& lint::operator=(lint const& other)
{
    if(other.bits_ != nullptr)
    {
        if(bits_ != nullptr)
        {
            *bits_ = *other.bits_;
        }
        
        bits_ = new vector<uint32_t>(*other.bits_);
    }
    else
    {
        bits_ = nullptr;
    }
    
    sign_ = other.sign_;
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

lint& lint::small_division(int num)
{
    if (std::abs(num) >= base)
    {
        return *this /= lint(num);
    }

    if (is_small())
    {
        sign_ /= num;
        return *this;
    }
    if (num < 0)
    {
        sign_ *= -1;
        num *= -1;
    }

    auto carry = 0;
    for (int i = bits_->size() - 1; i >= 0; --i) {
        long long cur = (*bits_)[i] + carry * 1ll * base;
        (*bits_)[i] = int(cur / num);
        carry = int(cur % num);
    }
    while (bits_->size() > 1 && bits_->back() == 0)
        bits_->pop_back();

    return *this;
}

void lint::unpack()
{
    if(!is_small())
    {
        return;
    }
    
    auto value = sign_;
    sign_ = sign_ >= 0 ? 1 : -1;

    bits_ = new vector<uint32_t>(2);
    (*bits_)[0] = value % base;
    (*bits_)[1] = value / base;
}

bool lint::is_zero() const
{
    return sign_ == 0 && bits_ == nullptr;
}

void lint::from_long_long(long long number)
{
    if (number >= 0 && number <= static_cast<long long>(INT32_MAX) ||
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

lint& lint::try_to_small()
{
    if(is_small() || bits_->size() != 1)
    {
        return *this;
    }

    if(sign_ == 1 && (*bits_)[0] <= INT32_MAX ||
        sign_ == -1 && (*bits_)[0] <= -INT32_MIN)
    {
        sign_ = sign_ * static_cast<int>((*bits_)[0]);
        delete bits_;
        bits_ = nullptr;
    }

    return *this;
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

    return cmp_bits(*l.bits_, *r.bits_) == 0;
}

bool apa::operator!=(lint const& l, lint const& r)
{
    return !(l == r);
}

bool apa::operator<(lint const& l, lint const& r)
{
    if (l.is_small() && r.is_small())
    {
        return l.sign_ < r.sign_;
    }

    if(l.is_small())
    {
        return r.sign_ == 1;
    }

    if(r.is_small())
    {
        return l.sign_ == -1;
    }

    if(r.sign_ != l.sign_)
    {
        return l.sign_ < r.sign_;
    }

    auto cmp_result = cmp_bits(*l.bits_, *r.bits_);

    return cmp_result == r.sign_;
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
    int k = 0;
    
    // small object optimize
    if(l.is_small() && r.is_small())
    {
        long long result = r.sign_ + l.sign_;
        l.from_long_long(result);
        return l;
    }

    if(l.is_small())
    {
        l.unpack();
    }

    auto right(r);
    right.unpack();

    uint32_t r_value;
    auto r_size = right.bits_->size();
    for (size_t i = 0; i < std::max(l.bits_->size(), r_size) || k; ++i)
    {
        while (l.bits_->size() <= i)
        {
            l.bits_->push_back(0);
        }
        
        r_value = (i < r_size ? (*right.bits_)[i] : 0);
        (*l.bits_)[i] += k + r_value;
        k = (*l.bits_)[i] >= lint::base;
        if (k)  (*l.bits_)[i] -= lint::base;
    }

    return l.try_to_small();
}

lint& apa::operator-=(lint& l, lint const&r)
{
    if(r.is_small() && l.is_small())
    {
        long long result = l.sign_ - r.sign_;
        l.from_long_long(result);
        return l;
    }

    if (l.is_small())
    {
        l.unpack();
    }

    auto right(r);
    right.unpack();

    auto k = 0;
    int result;
    for (size_t i = 0; i < right.bits_->size() || k; ++i) {
        result = (*l.bits_)[i] - (k + (i < right.bits_->size() ? (*right.bits_)[i] : 0));
        k = result < 0;
        if (k)
        {
            (*l.bits_)[i] = result + lint::base;
        }
        else
        {
            (*l.bits_)[i] = result;
        }
    }
    while (l.bits_->size() > 1 && l.bits_->back() == 0)
        l.bits_->pop_back();

    return l.try_to_small();
}

lint& apa::operator*=(lint& l, lint const&r)
{
    if(l.is_small() && r.is_small())
    {
        long long value = r.sign_ * l.sign_;
        l.from_long_long(value);
        return l;
    }

    if(l.is_small())
    {
        l.unpack();
    }

    auto right(r);
    right.unpack();
    
    lint c(0);
    c.unpack();

    for (auto i = 0; i < l.bits_->size(); ++i)
        for (auto j = 0, carry = 0; j < right.bits_->size() || carry; ++j) {
            while (c.bits_->size() <= i + j)
            {
                c.bits_->push_back(0);
            }

            long long cur = (*c.bits_)[i + j] + (*l.bits_)[i] * 1ll * (j < right.bits_->size() ? (*right.bits_)[j] : 0) + carry;
            (*c.bits_)[i + j] = (uint32_t) (cur % lint::base);
            carry = cur / lint::base;
        }

    while (c.bits_->size() > 1 && c.bits_->back() == 0)
        c.bits_->pop_back();

    l = c;
    return l.try_to_small();
}

lint& apa::operator/=(lint& l, lint const& r)
{
    if(l.is_small() && r.is_small())
    {
        auto value = l.sign_ / r.sign_;
        l.from_long_long(value);
        return l;
    }

    if(r.is_small() && std::abs(r.sign_) < lint::base)
    {
        return l.small_division(r.sign_);
    }

    if(l < r)
    {
        l = 0;
        return l;
    }

    if(l == r)
    {
        l = 1;
        return l;
    }

    if (l.is_small())
    {
        l.unpack();
    }

    lint left(1);
    auto right(r);
    right.unpack();
    lint center;
    lint lc;
    lint lcp;

    while(left <= right)
    {
        center = (left + right).small_division(2);
        lc = l * center;
        lcp = l * (center + 1);
        bool lesser = lc < r;
        if(lc == r || (lesser && lcp > r))
        {
            l = center;
            break;
        }
        std::cout << center.to_string() << std::endl;
        if (lesser)
        {
            left = center + 1;
        }
        else
        {
            right = center - 1;
        }
    }

    return l.try_to_small();
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
    stream << d.to_string();
    return stream;
}

std::istream& apa::operator>>(std::istream& stream, lint& d)
{
    std::string stream_data;
    stream >> stream_data;
    lint new_value(stream_data);
    d = new_value;
    return stream;
}

lint apa::abs(lint& other)
{
    return other > 0 ? other : -other;
}

lint apa::pow(lint& number, int degree)
{
    auto result(number);
    while(degree != 1)
    {
        if(degree % 2 == 0)
        {
            result *= result;
            degree /= 2;
        }
        else
        {
            result *= number;
            degree -= 1;
        }
    }

    return result;
}
