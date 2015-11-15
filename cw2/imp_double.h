#pragma once
#include <iostream>


namespace math {
    class imp_double
    {
    public:
        imp_double();
        imp_double(double value);
        imp_double(double value, double delta);

        imp_double operator-() const;

        imp_double & operator+= (imp_double const & other);
        imp_double & operator-= (imp_double const & other);
        imp_double & operator*= (imp_double const & other);
        imp_double & operator/= (imp_double const & other);

        double get_value() const;
        double get_delta() const;

    private:
        static constexpr double eps = 1e-15;
        double value_;
        double delta_;
    };

    imp_double operator+(imp_double, imp_double const&);
    imp_double operator-(imp_double, imp_double const&);
    imp_double operator*(imp_double, imp_double const&);
    imp_double operator/(imp_double, imp_double const&);

    bool operator<  (imp_double const & left, imp_double const & right);
    bool operator<= (imp_double const & left, imp_double const & right);
    bool operator>  (imp_double const & left, imp_double const & right);
    bool operator>= (imp_double const & left, imp_double const & right);
    bool operator== (imp_double const & left, imp_double const & right);
    bool operator!= (imp_double const & left, imp_double const & right);

    std::ostream & operator<< (std::ostream & stream, imp_double const & d);
    std::istream & operator>> (std::istream & stream, imp_double & d);
}