// Section 3 - 2.3 ~ 2.5
// Focus: floating point numbers
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    using namespace std;

    float f(3.141592f); // f 안붙이면 자동으로 double 3.14 * 100 = 3.14e2
    double d(3.141592);
    long double ld;

    cout << 3.14 << endl;
    cout << 31.4e-1 << endl;
    cout << 31.4e2 << endl;

    cout << std::setprecision(16) << endl; // 16자리 
    cout << 1.0 / 3.0 << endl;

    float f2(123456789.0f); // 10 significant digits
    cout << f2 << endl; // 123456792

    double d2(0.1);
    cout << d2 << endl; // 0.1
    cout << std::setprecision(17);
    cout << d2 << endl; // 0.10000000000000001

    double dt1(1.0);
    double dt2(0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1); // 오차 누적됨 

    cout << dt1 << endl;
    cout << dt2 << endl;

    double zero = 0.0;
    double posinf = 5.0 / zero;
    double neginf = -5.0 / zero;
    double nan = zero / zero;

    cout << posinf << " " << std::isinf(posinf) << endl;
    cout << neginf << " " << std::isinf(neginf) << endl;
    cout << nan << " " << std::isnan(nan) << endl;
    cout << 1.0 << " " << std::isinf(1.0) << endl;


    return 0;
}