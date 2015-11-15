#pragma once
#include <cstdint>
#include <string>

namespace apa
{
    class lint
    {
    public:
        lint();                    // ����������� �� ���������
        lint(std::string const&);  // ����������� �� ������
        lint(int);
        lint(long long);           // ����������� �� ������ �����
        lint(double);              // ����������� �� ������������� �����

        lint(lint const&);         // �����������

        explicit operator bool() const;
        explicit operator int() const;
        explicit operator long() const;

        lint& operator=(lint const&);
       // bool operator!(); // ����� ������                // ����������� ������������ � �������� ���������� (true, ���� �� ����)

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

        size_t rank_;       // ����� �������� ���������� �������
        size_t size_;       // ������� ������ ��������
        uint32_t* number_;  // ������ ��� �������� �����
        void move();
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
