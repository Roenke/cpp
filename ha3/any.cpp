#include "any.h"
utils::any::any()
{
    inner_ = nullptr;
}

bool utils::any::empty() const
{
    return inner_ == nullptr;
}

