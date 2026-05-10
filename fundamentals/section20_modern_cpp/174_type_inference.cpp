// Section 19 - 19.6 ~ 19.8
// Focus: type inference
#include<iostream>
#include<vector>
#include<algorithm> // std::min
// Reference : http://thbecker.net/articles/auto_and_decltype/section_01.html

using namespace std;

class Examples
{
public:
    void ex1()
    {
        std::vector<int> vect;
        for (std::vector<int>::iterator itr = vect.begin(); itr != vect.end(); ++itr)
            cout << *itr;
        
        for (auto itr = vect.begin(); itr != vect.end(); ++itr)
            cout << *itr;
        
        for (auto itr : vect) // for( const auto &itr: vect)
            cout << itr;
    }

    void ex2()
    {
        // auto는 가장 기본적인 자료형만 추론함
        int x = int();
        auto auto_x = x;

        const int &crx = x;
        auto auto_crx1 = crx;
        const auto& auto_crx2 = crx;

        volatile int vx = 1024;
        auto avx = vx;

        volatile auto vavx = vx;
    }

    // template<class T>
    // void func_ex3(T arg)
    // {}

    template<class T>
    void func_ex3(const T& arg)
    {}

    void ex3()
    {
        const int &crx = 123;
        func_ex3(crx);
    }

    void ex4()
    {
        const int c = 0;
        auto & rc = c;
        // rc = 123; // error 발생
        // rc는 const이기 때문.
    }

    void ex5() // amendment
    {
        int i = 42;
        auto&& ri_1 = i; // l-value
        auto&& ri_2 = 42; // r-value
    }

    void ex6()
    {
        int x = 42;
        const int *p1 = &x;
        auto p2 = p1;
        // *p2 = 43; // error
    }

    template<typename T, typename S> 
    void func_ex7(T lhs, S rhs)
    {
        auto prod1 = lhs * rhs;

        // 자료형을 변수로 만들어서 사용하는 방법
        typedef decltype(lhs * rhs) product_type;
        product_type prod2 = lhs * rhs;

        // decltype 바로 사용
        decltype(lhs * rhs) prod3 = lhs * rhs;
    }

    template<typename T, typename S>
    // decltype(lhs * rhs) func_ex8(T lhs, S rhs)
    auto func_ex8(T lhs, S rhs) -> decltype(lhs * rhs)
    {
        return lhs * rhs;
    }

    void ex7_8()
    {
        func_ex7(1.0, 345);
        func_ex8(1.2, 345);
    }

    struct S
    {
        int m_x;
        S()
        {
            m_x = 42;
        }
    };

    void ex9()
    {
        int x;
        const int cx = 42;
        const int& crx = x;
        const S *p = new S();

        auto a = x;
        auto b = cx;
        auto c = crx ;
        auto d = p;
        auto e = p->m_x;

        // 'declared' type
        // 선언이 된 타입을 그대로 가져온다. 
        // '&', '*' 도 그대로 가져온다.
        typedef decltype(x) x_type;
        typedef decltype(cx) cx_type;
        typedef decltype(crx) crx_type;
        typedef decltype(p->m_x) m_x_type;

        // add references to L-values
        // with const
        typedef decltype((x)) x_with_parens_type;
        typedef decltype((cx)) cx_with_parens_type;
        typedef decltype((crx)) crx_with_parens_type;
        typedef decltype((p->m_x)) m_w_with_parens_type;
    }

    const S foo()
    {
        return S();
    }

    int num = 123;
    const int& refnum = num;

    const int& foobar()
    {
        return refnum;
    }

    void ex10()
    {
        std::vector<int> vect = { 42, 43 };

        auto a = foo();
        typedef decltype(foo()) foo_type;

        auto b = foobar();
        typedef decltype(foobar()) foobar_type;

        auto itr = vect.begin();
        typedef decltype(vect.begin()) iterator_type;

        auto first_element = vect[0];
        decltype(vect[1]) second_element = vect[1];
    }

    void ex11()
    {
        int x = 0;
        int y = 0;
        
        const int cx = 42;
        const int cy = 43;

        double d1 = 3.14;
        double d2 = 2.72;

        // 1. typedef decltype으로 결정되는 데이터 타입과
        // 2. auto로 결정되는 데이터 타입 간의 
        // 차이를 확인
        typedef decltype(x * y) prod_xy_type;
        auto a = x * y;

        // result is pure R-value
        typedef decltype(cx * cy) prod_cxcy_type; 
        auto b = cx * cy;

        // result is L-value. 
        // '&' is added.
        // 2 변수의 데이터 타입이 같을 경우
        typedef decltype(d1 < d2 ? d1 : d2) cond_type;
        auto c = d1 < d2 ? d1 : d2;

        // promotion of x to double
        // 2 변수 데이터 타입이 다를 경우
        typedef decltype(x < d2 ? x : d2) cond_type_mixed;
        auto d = x < d2 ? x : d2;

        // auto d = std::min(x, dbl); // error 
        // 데이터 타입이 같아야 에러가 나지 않는다.
    }

    // floating point min = fpmin
    template<typename T, typename S>
    auto fpmin_wrong(T x, S y) -> decltype( x < y ? x : y)
    {
        return x < y ? x : y;
    }

    template<typename T, typename S>
    auto fpmin(T x, S y) -> typename std::remove_reference<decltype(x < y ? x : y)>:: type
    {
        return x < y ? x : y;
    } 

    void ex12()
    {
        int i = 42;
        double d = 45.1;
        // auto a = std::min(i, d) // error: 'std::min' : no matching overloaded function found
        auto a = std::min(static_cast<double>(i), d); 

        int &j = i;

        typedef decltype(fpmin_wrong(d, d)) fpmin_return_type1;
        typedef decltype(fpmin_wrong(i, d)) fpmin_return_type2;
        typedef decltype(fpmin_wrong(j, d)) fpmin_return_type2;
    }

    void ex13()
    {
        // vect is empty
        std::vector<int> vect;
        typedef decltype(vect[0]) integer;
    }

    template<typename R>
    class  SomeFunctor
    {
    public:
        typedef R result_type;

        SomeFunctor()
        {}

        result_type operator() ()
        {
            return R();
        }
    };

    void ex14()
    {
        SomeFunctor<int> func;
        typedef decltype(func)::result_type integer; // nested type
    }

    void ex15()
    {
        auto lambda = []() { return 42;};
        decltype(lambda) lambda2(lambda);
        decltype((lambda)) lambda3(lambda);

        cout << "Lambda functions" << endl;
        cout << &lambda << " " << &lambda2 << endl;
        cout << &lambda << " " << &lambda3 << endl;
    }

    void ex16()
    {
        // generic lambda
        auto lambda = []( auto x, auto y)
        {
            return x + y;
        };

        cout << lambda(1.1, 2) << " ";
        cout << lambda(3,4) << " ";
        cout << lambda(4.5, 2.2) << endl;
    }

};

int main()
{
    Examples examples;
    examples.ex1();
    examples.ex2();
    examples.ex3();
    examples.ex10();
    examples.ex12();
    examples.ex14();
    examples.ex15();
    examples.ex16();
    
    return 0;
}