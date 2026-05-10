// Section 19 - 19.6 ~ 19.8
// Focus: perfect forwarding
#include <iostream>
#include <vector>
#include <utility> // std::forward

class CustomVector
{
public:
    unsigned n_data = 0;
    int *ptr = nullptr;
public:
    CustomVector(const unsigned & _n_data, const int & _init = 0 )
    {
        std::cout << "Constructor" << "\n";

        init(_n_data, _init);
    }

    CustomVector(const CustomVector & l_input)
    {
        std::cout << "Copy constructor" << "\n";
        init(l_input.n_data);
        for (unsigned i = 0; i < n_data; ++i)
            ptr[i] = l_input.ptr[i];
    }

    CustomVector(CustomVector && r_input)
    {
        std::cout << "Move construcotr" << "\n";
        n_data = r_input.n_data;
        ptr = r_input.ptr;

        r_input.n_data = 0;
        r_input.ptr = nullptr;
    }

    ~CustomVector()
    {
        delete [] ptr;
    }

    void init(const unsigned & _n_data, const int & _init = 0)
    {
        n_data = _n_data;
        ptr = new int[n_data];
        for (unsigned i = 0; i < n_data; ++i)
            ptr[i] = _init;
    }
};

void doSomething(CustomVector & vec)
{
    std::cout << "pass by L value" << "\n";
    CustomVector new_vec(vec);
}

void doSomething(CustomVector && vec)
{
    std::cout << "pass by R value" << "\n";
    CustomVector new_vec(std::move(vec));
}

template<typename T>
void doSomethingTemplate(T && vec)
{
    doSomething(std::forward<T>(vec));
}
int main() 
{
    CustomVector vec(10, 1024);
    // CustomVector temp(std::move(vec));

    // std::cout << vec.n_data << "\n";
    
    // doSomething(vec);
    // doSomething(CustomVector(10, 8));

    doSomethingTemplate(vec);
    doSomethingTemplate(CustomVector(10, 8));

    return 0;
}