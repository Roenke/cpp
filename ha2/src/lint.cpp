#include "lint.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace apa;
using namespace helpers;
lint::lint()
    : sign_(0)
    , bits_(nullptr)
{
}

lint::lint(lint && other)
    : sign_(other.sign_)
    , bits_(nullptr)
{
    if(other.bits_ != nullptr)
    {
        bits_ = new bits(*other.bits_);
    }
}

lint::lint(std::string const& s)
    : sign_(0)
    , bits_(nullptr)
{
    auto str_length = s.length();
    if (str_length <= max_positive_small_length || (s[0] == '-' && str_length == max_negative_small_length))
    {
        sign_ = atoi(s.c_str());
        return;
    }

    sign_ = 1;
    bits_ = new bits(0);
    auto start_value = static_cast<int>(s.length());
    if (s[0] == '-')
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
	try_to_small();
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
    if (bits_ != nullptr)
    {
        delete bits_;
    }
}

lint::lint(lint const& other)
    : sign_(other.sign_)
    , bits_(nullptr)
{
    if (other.bits_ != nullptr)
    {
        bits_ = new bits(*other.bits_);
    }
}

lint::operator bool() const
{
    return sign_ != 0;
}

lint::operator int() const
{
    if (bits_ == nullptr)
    {
        return sign_;
    }

    if (sign_ == -1 && bits_->size() == 2 && (*bits_)[0] == 147483648 && (*bits_)[1] == 2)
    {
        return INT32_MIN;
    }

    return (*bits_)[0];
}

lint::operator long long() const
{
    if (bits_ != nullptr)
    {
        if (bits_->size() > 1)
        {
            return static_cast<long long>((*bits_)[0]) + base * (*bits_)[1];
        }

        return (*bits_)[0];
    }

    return sign_;
}

lint& lint::operator=(lint const& other)
{
    if (this == &other) return *this;
    
    delete bits_;
    if(other.bits_ == nullptr)
    {
        bits_ = nullptr;
    }
    else
    {
        bits_ = new bits(*other.bits_);
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
    sprintf(buf, "%u", static_cast<uint32_t>((*bits_)[static_cast<int>(size - 1)]));
    ost << buf;

    for (auto i = static_cast<int>(size - 2); i >= 0; --i)
    {
        sprintf(buf, "%09u", static_cast<uint32_t>((*bits_)[i]));
        ost << buf;
    }

    return ost.str();
}

lint& lint::small_division(int num)
{
    uint32_t divisor = std::abs(num);
    if (divisor >= base)
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
    if (!is_small())
    {
        return;
    }

    auto value = std::abs(sign_);
    sign_ = sign_ >= 0 ? 1 : -1;

    bits_ = new bits(2);
    (*bits_)[0] = value % base;
    (*bits_)[1] = value / base;
}

bool lint::is_zero() const
{
    return sign_ == 0 && bits_ == nullptr;
}

// magic eq transform for plus operation
bool apa::transform_plus(lint& l, lint const& r)
{
    if (l < 0 && r < 0)
    {
        l = -(-l + -r);
        return true;
    }

    if (l < 0)
    {
        l = (-l < r) ? r - (-l) : -((-l) - r);
        return true;
    }

    if (r < 0)
    {
        l = (-r < l) ? l - (-r) : -((-r) - l);
        return true;
    }

    return false;
}

// magic eq transform for substruct operation
bool apa::transform_minus(lint& l, lint const& r)
{
    if (l == 0)
    {
        l = -l;
        return true;
    }

    if (r == 0)
    {
        return true;
    }

    if (l > 0 && r > 0 && l < r)
    {
        l = -(r - l);
        return true;
    }

    if (l < 0 && r > 0)
    {
        l = -(-l + r);
        return true;
    }

    if (l > 0 && r < 0)
    {
        l = l + (-r);
        return true;
    }

    if (r < 0 && l < 0)
    {
        l = abs(l) > abs(r) ? -(-l - (-r)) : -r - (-l);
        return true;
    }

    return false;
}

// magic eq transform for division operation
bool apa::transdorm_div(lint& l, lint const& r)
{
    if (abs(l) < abs(r))
    {
        l = 0;
        return true;
    }

    if (l == r)
    {
        l = 1;
        return true;
    }

    return false;
}

void lint::from_long_long(long long number)
{
    if ((number >= 0 && number <= static_cast<long long>(INT32_MAX)) ||
        (number < 0 && number >= static_cast<long long>(-INT32_MAX)))
    {
        sign_ = static_cast<int>(number);
    }
    else
    {
        sign_ = number > 0 ? 1 : -1;
        number *= sign_;
		bits_ = new bits(0);
		while(number >= base)
		{
			bits_->push_back(number % base);
			number /= base;
		}
		if(number > 0)
		{
			bits_->push_back(number);
		}
    }
}

lint& lint::try_to_small()
{
    if (is_small())
    {
        return *this;
    }

    for (size_t i = 2; i < bits_->size(); ++i)
    {
        if ((*bits_)[i] != 0)
            return *this;
    }

    auto value = static_cast<long long>(static_cast<uint32_t>((*bits_)[0]));

    if (bits_->size() >= 2)
    {
        value += (*bits_)[1] * base;
    }

    if (value <= INT32_MAX)
    {
        sign_ = sign_ * static_cast<int>(value);
        delete bits_;
        bits_ = nullptr;
    }

    return *this;
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

    value -= 1;
    return old_value;
}

bool apa::operator==(lint const& l, lint const& r)
{
    if (l.sign_ != r.sign_)
    {
        return false;
    }
    if (l.bits_ == nullptr && r.bits_ == nullptr)
    {
        return true;
    }

    if (l.bits_ == nullptr || r.bits_ == nullptr)
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

    if (l.is_small())
    {
        return r.sign_ == 1;
    }

    if (r.is_small())
    {
        return l.sign_ == -1;
    }

    if (r.sign_ != l.sign_)
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

lint& lint::operator+=(lint const&r)
{
    // small object optimize
    if (is_small() && r.is_small())
    {
        auto result = static_cast<long long>(r.sign_) + sign_;
        from_long_long(result);
        return *this;
    }

    if (transform_plus(*this, r))
    {
        return *this;
    }

    if (is_small())
    {
        unpack();
    }

    auto right(r);
    right.unpack();

    int k = 0;
    uint32_t r_value;
    auto r_size = right.bits_->size();
    for (size_t i = 0; i < std::max(bits_->size(), r_size) || k; ++i)
    {
        while (bits_->size() <= i)
        {
            bits_->push_back(0);
        }

        r_value = (i < r_size ? (*right.bits_)[i] : 0);
        (*bits_)[i] = (*bits_)[i] + k + r_value;
        k = (*bits_)[i] >= base;
        if (k)  (*bits_)[i] = (*bits_)[i] - static_cast<uint32_t>(base);
    }

    return try_to_small();
}

lint& apa::lint::operator-=(lint const&r)
{
    if (r.is_small() && is_small())
    {
        auto result = static_cast<long long>(sign_) - r.sign_;
        from_long_long(result);
        return *this;
    }

    if (transform_minus(*this, r))
    {
        return *this;
    }

    if (is_small())
    {
        unpack();
    }

    auto right(r);
    right.unpack();
    if (right.bits_->size() > bits_->size())
    {
        bits_->resize(right.bits_->size());
    }

    auto k = 0;
    int result;
    for (size_t i = 0; i < right.bits_->size() || k; ++i)
    {
        if (bits_->size() <= i)
        {
            bits_->push_back(0);
        }

        result = (*bits_)[i] - (k + (i < right.bits_->size() ? (*right.bits_)[i] : 0));
        k = result < 0;
        if (k)
        {
            (*bits_)[i] = result + lint::base;
        }
        else
        {
            (*bits_)[i] = result;
        }
    }

    while (bits_->size() > 1 && bits_->back() == 0)
        bits_->pop_back();

    return try_to_small();
}

lint& lint::operator*=(lint const& r)
{
    if (is_small() && r.is_small())
    {
        auto value = static_cast<long long>(r.sign_) * sign_;
        from_long_long(value);
        return *this;
    }

    if (is_small())
    {
        unpack();
    }

    auto right(r);
    right.unpack();

    lint c(0);
    c.unpack();

    c.bits_->resize(bits_->size() + right.bits_->size());
    c.sign_ = sign_ * right.sign_;
    for (size_t i = 0; i < bits_->size(); ++i)
    {
        for (size_t j = 0, carry = 0; j < right.bits_->size() || carry; ++j)
        {
            auto cur = (*c.bits_)[i + j] + (*bits_)[i] * 1ll * (j < right.bits_->size() ? (*right.bits_)[j] : 0) + carry;
            (*c.bits_)[i + j] = static_cast<uint32_t>(cur % lint::base);
            carry = static_cast<int>(cur / lint::base);
        }
    }

    while (c.bits_->size() > 1 && c.bits_->back() == 0)
        c.bits_->pop_back();

    *this = c;
    return try_to_small();
}

lint& lint::operator/=(lint const& r)
{
    if (r.is_small() && r == 0)
    {
        (void)(23 / r.sign_);
    }

    if (is_small() && r.is_small())
    {
        auto value = sign_ / r.sign_;
        from_long_long(value);
        return *this;
    }

    uint32_t divisor_abs = std::abs(r.sign_);
    if (r.is_small()&& divisor_abs < lint::base)
    {
		*this = small_division(r.sign_);
		return try_to_small();
    }

    if (transdorm_div(*this, r))
    {
        return *this;
    }

    if (is_small())
    {
        unpack();
    }


    lint left(0);
    auto abs_r = abs(r);
	abs_r.unpack();
    auto abs_l = abs(*this);
    auto right(abs_l);
    right.unpack();
    lint center;
    lint lc;
    lint lcp;

    while (left <= right)
    {
        center = (left + right).small_division(2);
        lc = abs_r * center;
        lcp = abs_r * (center + 1);
        bool lesser = lc < abs_l;
        if ((!lesser && lc == abs_l) || (lesser && lcp > abs_l))
        {
            break;
        }
        if (lesser)
        {
            left = center + 1;
        }
        else
        {
            right = center - 1;
        }
    }

    *this = sign_ * (r.sign_ >= 0 ? 1 : -1) * center;
    return try_to_small();
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

lint apa::abs(lint const& other)
{
    return other > 0 ? other : -other;
}

lint apa::pow(lint const& number, long long degree)
{
    lint result = 1;
    auto acc = number;
    if (degree == 0)
    {
        return 1;
    }

    while (degree != 0)
    {
        if (degree % 2 == 0)
        {
            acc *= acc;
            degree /= 2;
        }
        else
        {
            result *= acc;
            --degree;
        }
    }

    return result;
}
