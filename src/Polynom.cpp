#include "Polynom.h"

Polynom::Polynom()
{
    _arg = vector<double>(1, 0);
}
Polynom::Polynom(double args[], size_t size)
{
    for(int i = 0; i < size; i++)
        _arg.push_back(args[i]);
}
Polynom::Polynom(initializer_list<double> arg_list)
{
    for(double arg : arg_list)
        _arg.push_back(arg);
}
Polynom::Polynom(Polynom &p)
{
    for(double a : p._arg)
        _arg.push_back(a);
}
Polynom::Polynom(Polynom &&p)
{
    for(double a : p._arg)
        _arg.push_back(a);
}
Polynom& Polynom::operator=(Polynom &p)
{
    for(double a : p._arg)
        _arg.push_back(a);
}
Polynom& Polynom::operator=(Polynom &&p)
{
    for(double a : p._arg)
        _arg.push_back(a);
}
Polynom::~Polynom()
{
    //dtor
}

double Polynom::at(double var)
{
    double output = _arg[0];

    for(int i=1; i<_arg.size(); i++)    output += _arg[i] * pow(var, i);

    return output;
}

/// This is a declaration of one-argument overloaded operator +,
/// however I cannot use it with two-argument operator +, beacouse
/// it takes the same arguments. I implemented the version that will
/// add integers below.
//Polynom Polynom::operator+(Polynom &poly2) const
//{
//    size_t size = (_arg.size() > poly2._arg.size() ? _arg.size() : poly2._arg.size());
//    double *out = new double[size];
//
//    if(_arg.size() >= poly2._arg.size())
//    {
//        for(int i = 0; i<_arg.size(); i++)
//        {
//            if(i<poly2._arg.size()) out[i] = _arg[i] + poly2._arg[i];
//            else                    out[i] = _arg[i];
//        }
//    }
//    else
//    {
//        for(int i = 0; i<poly2._arg.size(); i++)
//        {
//            if(i<poly2._arg.size()) out[i] = poly2._arg[i] + _arg[i];
//            else                    out[i] = poly2._arg[i];
//        }
//    }
//
//    Polynom output = Polynom(out, size);
//    delete out;
//    return output;
//}
Polynom Polynom::operator+(int val) const
{
    Polynom output;
    output._arg = _arg;
    output._arg[0] += val;
    return output;
}
/// This is a declaration of one-argument overloaded operator -,
/// however I cannot use it with two-argument operator -, beacouse
/// it takes the same arguments. I implemented the version that will
/// add integers below.
//Polynom Polynom::operator-(Polynom &poly2) const
//{
//    size_t size = (_arg.size() > poly2._arg.size() ? _arg.size() : poly2._arg.size());
//    double *out = new double[size];
//
//    if(_arg.size() >= poly2._arg.size())
//    {
//        for(int i = 0; i<_arg.size(); i++)
//        {
//            if(i<poly2._arg.size()) out[i] = _arg[i] - poly2._arg[i];
//            else                    out[i] = _arg[i];
//        }
//    }
//    else
//    {
//        for(int i = 0; i<poly2._arg.size(); i++)
//        {
//            if(i<poly2._arg.size()) out[i] = poly2._arg[i] - _arg[i];
//            else                    out[i] = poly2._arg[i];
//        }
//    }
//
//    Polynom output = Polynom(out, size);
//    delete out;
//    return output;
//}
Polynom Polynom::operator-(int val) const
{
    Polynom output;
    output._arg = _arg;
    output._arg[0] -= val;
    return output;
}
Polynom Polynom::operator/(const Polynom &poly2)
{
    if(poly2._arg.size() == 1 && poly2._arg[0] == 0)    throw std::domain_error("Cannot divide by 0");

    size_t size = _arg.size() - poly2._arg.size() + 1;
    double *out = new double[size];
    int out_iter = size-1;
    Polynom copy = *this;
    double result;

    for(int i=0; i<size; i++)   out[i] = 0;

    for(int l=copy._arg.size()-1; l>=poly2._arg.size()-1; l--)
    {
        result = copy._arg[l]/poly2._arg.back();
        out[out_iter] += result;
        out_iter--;

        for(int r = poly2._arg.size()-1, l_c=l; r>=0; r--, l_c--)
            copy._arg[l_c] -= poly2._arg[r]*result;
    }

    Polynom output = Polynom(out, size);
    delete out;
    return output;

}
Polynom Polynom::operator%(const Polynom &poly2)
{
    if(poly2._arg.size() == 1 && poly2._arg[0] == 0)    throw std::domain_error("Cannot divide by 0");

    Polynom copy = *this;
    double result;


    for(int l=copy._arg.size()-1; l>=poly2._arg.size()-1; l--)
    {
        result = copy._arg[l]/poly2._arg.back();

        for(int r = poly2._arg.size()-1, l_c=l; r>=0; r--, l_c--)
            copy._arg[l_c] -= poly2._arg[r]*result;
    }

    return copy;
}

polydiv_t Polynom::polydiv(Polynom &lhs, Polynom &rhs)
{
    polydiv_t output;
    output.quot = lhs/rhs;
    output.rem = lhs%rhs;
    return output;
}

Polynom operator+(const Polynom &lhs, const Polynom &rhs)
{
    size_t size = (lhs._arg.size() > rhs._arg.size() ? lhs._arg.size() : rhs._arg.size());
    double *out = new double[size];

    if(lhs._arg.size() >= rhs._arg.size())
    {
        for(int i = 0; i<lhs._arg.size(); i++)
        {
            if(i<rhs._arg.size())   out[i] = lhs._arg[i] + rhs._arg[i];
            else                    out[i] = lhs._arg[i];
        }
    }
    else
    {
        for(int i = 0; i<rhs._arg.size(); i++)
        {
            if(i<rhs._arg.size())   out[i] = rhs._arg[i] + lhs._arg[i];
            else                    out[i] = rhs._arg[i];
        }
    }

    Polynom output = Polynom(out, size);
    delete out;
    return output;
}
Polynom operator-(const Polynom &lhs, const Polynom &rhs)
{
    size_t size = (lhs._arg.size() > rhs._arg.size() ? lhs._arg.size() : rhs._arg.size());
    double *out = new double[size];

    if(lhs._arg.size() >= rhs._arg.size())
    {
        for(int i = 0; i<lhs._arg.size(); i++)
        {
            if(i<rhs._arg.size())   out[i] = lhs._arg[i] - rhs._arg[i];
            else                    out[i] = lhs._arg[i];
        }
    }
    else
    {
        for(int i = 0; i<rhs._arg.size(); i++)
        {
            if(i<rhs._arg.size())   out[i] = rhs._arg[i] - lhs._arg[i];
            else                    out[i] = rhs._arg[i];
        }
    }

    Polynom output = Polynom(out, size);
    delete out;
    return output;
}
Polynom operator*(const Polynom &lhs, const Polynom &rhs)
{
    size_t size = lhs._arg.size() + rhs._arg.size() - 1;
    double *out = new double[size];

    for(int i=0; i<size; i++)   out[i] = 0;

    for(int l=0; l<lhs._arg.size(); l++)
    {
        for(int r=0; r<rhs._arg.size(); r++)
        {
            out[l+r] += lhs._arg[l] * rhs._arg[r];
        }
    }

    Polynom output = Polynom(out, size);
    delete out;
    return output;
}

ostream& operator<<(ostream &s, const Polynom &p)
{
    s<<"[ ";

    bool allZeros = true;
    for(int i=0; i<p._arg.size(); i++)
        if(p._arg[i]!=0)  allZeros = false;


    if(allZeros)    s<<0;
    else
    {
        for(int i = p._arg.size(); i >= 0; i--)
        {
            if(i==0 && p._arg[i]!=0)
            {
                if(p._arg[i]>=0)     s << "+" << p._arg[i];
                else                s << "-" << -1*p._arg[i];
            }
            else if(p._arg[i]!=0)
            {
                if(p._arg[i]>0)     s << "+" << p._arg[i] << "x^" << i;
                else                s << "-" << -1*p._arg[i] << "x^" << i;
            }
        }
    }

    s<<" ]";

    return s;
}
