#include <iostream>
#include <iterator>

#include "Polynom.h"

int main()
{
    using std::cout;

    Polynom a{7, 0, 0, 3, 0, 1};
    Polynom b{ 1, 0, 0, 1};
    cout << a/b << "\n" << a%b << "\n";

    double arr[] = {1, 2, 3, 4};
    Polynom p(arr, 4), q{1, 2, 3}, r;
    cout << "p = " << p << "\n"
        << "q = " << q << "\n";
    Polynom ppq = p + q, ppqmp = ppq - p;
    cout << "p+q = " << ppq << "\n";
    cout << "p+q-p = " << ppqmp << "\n";
    Polynom s{1, 0, 1}, prod = q * s;
    cout << "q*{1,0,1} = " << prod << "\n";
    Polynom t = (prod * r);
    cout << "Is it 0?" << prod * r << "\n";

    Polynom P{1, -1, 1, 1}, D{-1, 0, 2};
    polydiv_t res = Polynom::polydiv(P, D);
    cout << "P = " << P << "\n"
        << "D = " << D << "\n";
    cout << P << " = \n" << D << "*" << res.quot
    << "\n+ " << res.rem << "\n";
    Polynom Q{P/D};
    Polynom R{P%D};
    cout << "P/D = " << Q << "\n";
    cout << "P%D = " << R << "\n";
    cout << "Q*D+R-P = " << Q*D + R - P << "\n";

    double x{2};
    Polynom V{7};
    cout << "P(" << x << ") = " << P.at(x) << "\n";
    cout << "V(" << x << ") = " << V.at(x) << "\n";

    return 0;
}
