// Section 3 - 2.3 ~ 2.5
// Focus: floating point numbers
#include <iostream>
#include <cstdint> // 이 헤더 필요

int main() 
{
    using namespace std;

    std::int16_t i(5); // 16비트 
    std::int8_t myint = 65; // char로 교체 

    cout << myint << endl; // 문자로 해석
    cout << int(myint) << endl; // 해결

    std::int_fast8_t fi(5); // 8비트 중 빠른 것 
    std::int_least64_t fl(5); // 적어도 64비트를 같는 데이터 타입

    //void my_void 선언 불가 

    int j = 123;
    float f = 123.456f;

    void *my_void;

    my_void = (void*)&j; // 0x61fef8
    cout << my_void << endl;
    
    my_void = (void*)&f; // 0x61fef4
    cout << my_void << endl;



    return 0;
}