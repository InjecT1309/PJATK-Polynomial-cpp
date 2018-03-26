#ifndef POLYNOM_H
#define POLYNOM_H

#include <cmath>
#include <vector>
#include <initializer_list>
#include <ostream>
#include <exception>

using std::vector;
using std::initializer_list;
using std::ostream;

struct polydiv_t;

class Polynom
{
    public:
        Polynom();
        Polynom(double args[], size_t size);
        Polynom(initializer_list<double> arg_list);
        Polynom(Polynom &p);
        Polynom(Polynom &&p);
        Polynom& operator=(Polynom &p);
        Polynom& operator=(Polynom &&p);
        virtual ~Polynom();

        double at(double arg);

//        Polynom operator+(const Polynom &poly2) const;
        Polynom operator+(int val) const;
//        Polynom operator-(const Polynom &poly2) const;
        Polynom operator-(int val) const;
        Polynom operator/(const Polynom &poly2);
        Polynom operator%(const Polynom &poly2);

        static polydiv_t polydiv(Polynom &lhs, Polynom &rhs);

        friend Polynom operator+(const Polynom &lhs, const Polynom &rhs);
        friend Polynom operator-(const Polynom &lhs, const Polynom &rhs);
        friend Polynom operator*(const Polynom &lhs, const Polynom &rhs);


        friend ostream& operator<<(ostream &s, const Polynom &p);
    protected:
    private:
        vector<double> _arg;
};

struct polydiv_t
{
    Polynom quot;
    Polynom rem;
};

#endif // POLYNOM_H
