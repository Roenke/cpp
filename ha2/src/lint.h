#pragma once
#include <cstdint>
#include <string>

namespace apa
{
    class lint
    {
    public:
        lint();                    //  онструктор по умолчанию
        lint(std::string const&);  //  онструктор от строки
        lint(int);
        lint(long long);           //  онструктор от целого числа
        lint(double);              //  онструктор от вещественного числа

        lint(lint const&);         //  опирование

        explicit operator bool() const;
        explicit operator int() const;
        explicit operator long() const;

        lint& operator=(lint const&);
       // bool operator!(); // вроде лишнее                // ¬озможность использовать в условных выражени€х (true, если не ноль)

        lint& operator+();
        lint& operator-();

        std::string to_string();

        friend bool operator==(lint const&, lint const&);
        friend bool operator< (lint const&, lint const&);

        friend lint& operator+=(lint&, lint const&);
        friend lint& operator-=(lint&, lint const&);
        friend lint& operator*=(lint&, lint const&);
        friend lint& operator/=(lint&, lint const&);

    private:
        static uint32_t constexpr base = 4294967296;
        
        uint8_t sign_;

        size_t rank_;       // номер старшего ненулевого разр€да
        size_t size_;       // сколько пам€ти выделено
        uint32_t* number_;  // массив дл€ хранени€ числа
        void move();
    };

    // »нкремент
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
