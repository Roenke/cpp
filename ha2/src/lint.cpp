#include "lint.h"

using namespace apa;

lint::lint()
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

lint::lint(lint const& from)
    : sign_(from.sign_)
    , rank_(from.rank_)
    , size_(from.size_)
{
    number_ = new uint32_t[from.rank_];
    for (int i = 0; i < rank_; ++i)
    {
        number_[i] = from.number_[i];
    }
}

lint::operator bool() const
{
    return rank_ > 0;
}

lint& lint::operator=(lint const& from)
{
    if(rank_ != from.rank_)
    {
        delete[] number_;
        number_ = new uint32_t[from.rank_];
    }

    for (auto i = 0; i < from.rank_; ++i)
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

void lint::move()
{
    if(rank_ == size_)
    {
        size_t i;
        auto new_memory = new uint32_t[2 * size_];
        for (i = 0; i < size_; ++i)
        {
            new_memory[i] = number_[i];
        }

        size_ *= 2;
        std::swap(number_, new_memory);
        delete[] new_memory;
    }
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
    l.number_[0] += r.number_[0];

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

lint apa::abs(lint& other)
{
    return other > 0 ? other : -other;
}

lint apa::pow(lint&, int)
{
    // stub. ToDo: implement O(log(n)) pow
    return 0;
}
