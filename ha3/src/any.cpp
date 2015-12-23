#include "any.h"

utils::any::inner_base::~inner_base()
{}

utils::any::any()
    : inner_(nullptr)
{
}

utils::any::~any()
{
    delete inner_;
}

utils::any::any(any const& other)
    : inner_(other.empty() ? nullptr : other.inner_->clone())
{
}

utils::any& utils::any::operator=(any other)
{
    swap(*this, other);
    return *this;
}

std::type_info const& utils::any::type() const
{
    return inner_->type();
}

bool utils::any::empty() const
{
    return inner_ == nullptr;
}

utils::bad_any_cast::bad_any_cast(std::string const& what)
    : type_(what)
{}

char const* utils::bad_any_cast::what() const throw()
{
    auto str = std::string("Bad cast exception to type: ") + type_;
    return str.c_str();
}
