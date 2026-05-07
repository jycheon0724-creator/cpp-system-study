// Section 19 - 19.1 ~ 19.2
// Focus: mulitple values return 
#include <iostream>
#include <tuple>

auto my_func()
{
    return std::tuple(123, 456, 789);
}
int main() 
{
    // auto result = my_func();

    // std::cout << std::get<0>(result) << " " << std::get<1>(result) << "\n";    

    auto[a, b, c] = my_func();

    std::cout << a << " " << b << " " << c << "\n";
    return 0;
}