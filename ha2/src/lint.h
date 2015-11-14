#pragma once
#include <cstdint>
#include <string>
#include "vector.h"

namespace apa
{
    struct lint
    {
        lint();                    // ����������� �� ���������
        lint(std::string const&);  // ����������� �� ������
        lint(int);
        lint(long long);           // ����������� �� ������ �����
        explicit lint(double);     // ����������� �� ������������� �����

        lint(lint const&);         // �����������

        explicit operator bool() const;
        explicit operator int() const;
        explicit operator long() const;

        lint& operator=(lint const&);
       // bool operator!(); // ����� ������                // ����������� ������������ � �������� ���������� (true, ���� �� ����)

        lint& operator+();
        lint& operator-();

        bool is_small() const;

        std::string to_string() const;

        friend bool operator==(lint const&, lint const&);
        friend bool operator< (lint const&, lint const&);

        friend lint& operator+=(lint&, lint const&);
        friend lint& operator-=(lint&, lint const&);
        friend lint& operator*=(lint&, lint const&);
        friend lint& operator/=(lint&, lint const&);

    private:
        static uint64_t constexpr base = 1000000000;
        
        int sign_;
        helpers::vector<uint32_t>* bits_;
    };

    // ���������
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
