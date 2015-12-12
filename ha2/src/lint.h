#pragma once
#include <cstdint>
#include <string>
#include "bits.h"

namespace apa
{
    struct lint
    {
        lint();                    // Конструктор по умолчанию
        lint(std::string const&);  // Конструктор от строки
        lint(int);
        lint(long long);           // Конструктор от целого числа
        explicit lint(double);     // Конструктор от вещественного числа
        ~lint();

        lint(lint const&);         // Копирование

        explicit operator bool() const;
        explicit operator int() const;
        explicit operator long long() const;

        lint& operator=(lint const&);

        lint operator+() const;
        lint operator-() const;

        bool is_small() const;

        std::string to_string() const;

        friend bool operator==(lint const&, lint const&);
        friend bool operator< (lint const&, lint const&);

        lint& operator+=(lint const&);
        lint& operator-=(lint const&);
        lint& operator*=(lint const&);
        lint& operator/=(lint const&);

    private:
        static uint64_t constexpr base = 1000 * 1000 * 1000;
        
        int sign_;
        helpers::bits* bits_;

        void unpack(); // unsafe method.
        bool is_zero() const;
        void from_long_long(long long);
        lint& try_to_small();
        void assert_optimization() const;
        lint& small_division(int);
    };

    // Инкремент
    lint& operator++(lint&);       // prefix
    lint  operator++(lint&, int);  // postfix

    lint& operator--(lint&);       // prefix
    lint  operator--(lint&, int);  // postfix

    bool operator==(lint const&, lint const&);
    bool operator!=(lint const&, lint const&);
    bool operator< (lint const&, lint const&);
    bool operator> (lint const&, lint const&);
    bool operator>=(lint const&, lint const&);
    bool operator<=(lint const&, lint const&);

    lint operator+(lint, lint const&);
    lint operator-(lint, lint const&);
    lint operator*(lint, lint const&);
    lint operator/(lint, lint const&);

    bool transform_plus(lint&, lint const&);
    bool transform_minus(lint&, lint const&);
    bool transdorm_div(lint&, lint const&);

    std::ostream & operator<< (std::ostream & stream, lint const & d);
    std::istream & operator>> (std::istream & stream, lint & d);

    lint abs(lint const&);
    lint pow(lint const&, long long);
}; /* apa */
