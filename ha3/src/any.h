#pragma once
#include <exception>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace utils
{
    class any
    {
        /* additional structures */
        struct inner_base
        {
            virtual ~inner_base();
            virtual std::type_info const& type() const = 0;
            virtual inner_base* clone() const = 0;
        };

        template<typename T>
        struct inner : inner_base
        {
            explicit inner(T const& value);
            std::type_info const& type() const override;
            inner_base* clone() const override;
        private:
            T value_;

            template<typename U>
            friend U* any_cast(any*);
        };
    public:
        any();
        template<typename T>
        explicit any(T const&);
        any(any const&);

        template<typename T>
        any& operator=(T const&);
        any& operator=(any);

        ~any();

        std::type_info const& type() const;
        bool empty() const;

        friend void swap(any& l, any& r);
    private:
        inner_base* inner_;

        template<typename ValueType>
        friend ValueType* any_cast(any * operand);
    };

    class bad_any_cast : public std::bad_cast
    {
    public:
        explicit bad_any_cast(std::string const&);

        virtual const char* what() const noexcept override;

    private:
        std::string what_;
    };

    template<typename T> T any_cast(any & operand);
    template<typename T> T any_cast(const any & operand);
    template<typename ValueType>       ValueType * any_cast(any * operand);
    template<typename ValueType> const ValueType * any_cast(const any * operand);

    template <typename T>
    any::inner<T>::inner(T const& value)
        : value_(value)
    {}

    template <typename T>
    std::type_info const& any::inner<T>::type() const
    {
        return typeid(T);
    }

    template <typename T>
    any::inner_base* any::inner<T>::clone() const
    {
        return new inner(value_);
    }

    inline void swap(any& l, any& r)
    {
        std::swap(l.inner_, r.inner_);
    }

    template <typename T>
    any::any(T const& value)
        : inner_(new inner<const T>(value))
    {}

    template <typename T>
    any& any::operator=(T const& other)
    {
        any res(other);
        swap(*this, res);
        return *this;
    }
}; /* utils */

template <typename T>
T utils::any_cast(any& operand)
{
    auto cast_result = any_cast<typename std::remove_reference<T>::type>(&operand);
    if (cast_result == nullptr)
    {
        throw bad_any_cast(typeid(T).name());
    }

    return static_cast<T>(*cast_result);
}

template <typename T>
T utils::any_cast(const any& operand)
{
    return any_cast<typename std::remove_reference<T>::type const&>(const_cast<any&>(operand));
}

template <typename ValueType> ValueType* utils::any_cast(utils::any * operand)
{
    if (operand != nullptr && operand->type() == typeid(ValueType))
    {
        return &static_cast<any::inner<ValueType>*>(operand->inner_)->value_;
    }

    return nullptr;
}

template <typename ValueType>
const ValueType* utils::any_cast(const any* operand)
{
    return any_cast<ValueType>(const_cast<utils::any*>(operand));
}
