#pragma once
#include <cstdint>
#include <string>

namespace apa
{
    class lint
    {
    public:
        lint();                    // Конструктор по умолчанию
        lint(std::string const&);  // Конструктор от строки
        lint(int);
        lint(long long);           // Конструктор от целого числа
        lint(double);              // Конструктор от вещественного числа

        lint(lint const&);         // Копирование

        explicit operator bool();
        explicit operator int();
        explicit operator long();

        int operator=(lint const&);
        bool operator!();          // Возможность использовать в условных выражениях (true, если не ноль)

        lint& operator+();
        lint& operator-();

        std::string to_string();

    private:
        static uint32_t constexpr base = 4294967296;
    };

    // Инкремент
    lint& operator++(lint&);       // prefix
    lint operator++ (lint&, int);  // postfix

    lint& operator--(lint&);       // prefix
    lint operator-- (lint&, int);  // postfix

    bool operator==(lint const&, lint const&);
    bool operator!=(lint const&, lint const&);
    bool operator< (lint const&, lint const&);
    bool operator> (lint const&, lint const&);
    bool operator>=(lint const&, lint const&);
    bool operator<=(lint const&, lint const&);

    lint& operator+=(lint&, lint const&);
    lint& operator-=(lint&, lint const&);
    lint& operator*=(lint&, lint const&);
    lint& operator/=(lint&, lint const&);

    lint operator+(lint, lint const&);
    lint operator-(lint, lint const&);
    lint operator*(lint, lint const&);
    lint operator/(lint, lint const&);

    std::ostream & operator<< (std::ostream & stream, lint const & d);
    std::istream & operator>> (std::istream & stream, lint & d);

    lint abs(lint&);
    lint pow(lint&, int);
}; /* apa */
