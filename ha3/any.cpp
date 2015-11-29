#include "any.h"
utils::any::any()
{
    inner_ = nullptr;
}

utils::any::any(any const& other)
{
    //inner_ = other.inner_->clone();
}

utils::any& utils::any::operator=(any other)
{
    swap(*this, other);
    return *this;
}

bool utils::any::empty() const
{
    return inner_ == nullptr;
}

