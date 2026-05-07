// Section 19 - 19.1 ~ 19.2
// Focus: lambda
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

void goodbye(const std::string & s)
{
    std::cout << "good bye " << s << "\n";
}

class Object 
{
public: 
    void hello(const std::string & s)
    {
        std::cout << "Hello " << s << "\n";
    }
};

int main() 
{
    // lambda introducer
    // lambda parameter declaration 
    // lambda return type clause 
    // compound statement 
    auto func = [](const int & i) -> void {std::cout << "Hello world" << "\n"; };
    func(123);

    {
        std::string name = "JackJack";
        [&]() {std::cout << name << "\n";}();
    }

    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);

    auto func2 = [](int val) { std::cout << val << "\n"; };
    std::for_each(v.begin(), v.end(), func2);

    std::for_each(v.begin(), v.end(), [](int val) {std::cout << val << "\n";});

    std::cout << []() -> int { return 1;}() << "\n";

    std::function<void(int)> func3 = func2;
    func3(123);

    std::function<void()>func4 = std::bind(func3, 456);
    func4();

    {
        Object instance;
        auto f = std::bind(&Object::hello, &instance, std::placeholders::_1);

        f(std::string("World"));

        auto f2 = std::bind(&goodbye, std::placeholders::_1);

        f2(std::string("World"));
    }
    return 0;
}