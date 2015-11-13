#include "lint.h"
#include <cassert>
#include <algorithm>
using namespace apa;

lint::lint()
    : sign_(0)
    , rank_(1)
    , size_(1)
    , number_(new uint32_t[1])
{
    number_[0] = 0;
}

// stub
lint::lint(std::string const&)
    : sign_(0)
    , rank_(1)
    , size_(1)
    , number_(new uint32_t[1])
{
    number_[0] = 0;
}

lint::lint(int number)
    : sign_(0)
    , rank_(1)
    , size_(1)
    , number_(new uint32_t[1])
{
    number_[0] = number;
}

lint::lint(long long number)
    : sign_(0)
    , rank_(2)
    , size_(2)
    , number_(new uint32_t[2])
{
    number_[0] = static_cast<uint32_t>(number % static_cast<uint64_t>(base));
    number_[1] = static_cast<uint32_t>(number / static_cast<uint64_t>(base));
}

lint::lint(double)
    : sign_(0)
    , rank_(1)
    , size_(1)
    , number_(new uint32_t[1])
{
    number_[0] = 0;
}

lint::lint(lint const& from)
    : sign_(from.sign_)
    , rank_(from.rank_)
    , size_(from.size_)
{
    number_ = new uint32_t[from.rank_];
    for (size_t i = 0; i < rank_; ++i)
    {
        number_[i] = from.number_[i];
    }
}

lint::operator bool() const
{
    return rank_ > 0;
}

lint::operator int() const
{
    return 0;
}

lint::operator long() const
{
    return 0L;
}

lint& lint::operator=(lint const& from)
{
    if(rank_ != from.rank_)
    {
        delete[] number_;
        number_ = new uint32_t[from.rank_];
    }

    for (size_t i = 0; i < from.rank_; ++i)
    {
        number_[i] = from.number_[i];
    }

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

void lint::alloc(uint32_t new_size = -1)
{
    assert(new_size == -1 || new_size > 0);
    size_t new_size_value = 1;
    if(new_size == -1)
    {
        new_size_value = size_ * 2;
    }
    else
    {
        while (new_size_value <= new_size) new_size_value *= 2;
    }

    size_t i;
    auto new_memory = new uint32_t[new_size_value];
    for (i = 0; i < size_; ++i)
    {
        new_memory[i] = number_[i];
    }

    size_ = new_size_value;
    delete[] number_;

    std::swap(number_, new_memory);
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
    if(l.rank_ == r.rank_)
    {
        for (int i = l.rank_; i >= 0; --i)
        {
            if(l.number_[i] != r.number_[i])
            {
                return false;
            }
        }
    }

    return true;
}

bool apa::operator!=(lint const& l, lint const& r)
{
    return !(l == r);
}

bool apa::operator<(lint const& l, lint const& r)
{
    if(l.rank_ != r.rank_)
    {
        return l.rank_ < r.rank_;
    }

    for (int i = l.rank_; i >= 0; --i)
    {
        if(r.number_[i] >= l.number_[i])
        {
            return false;
        }
    }

    return true;
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
    if (l.rank_ + 1 < r.rank_)
    {
        l.alloc(r.rank_);
    }

    uint32_t k = 0;
    uint64_t acc;
    auto min_length = std::min(l.rank_, r.rank_);
    size_t j;
    for (j = 0; j < min_length; ++j)
    {
        acc = l.number_[j] + r.number_[j] + k;
        k = acc / lint::base;
        l.number_[j] = acc % lint::base;
    }

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
