#include <random>
#include <string>
#include <iostream>
#include <algorithm>
#include <string_view>

std::string make_password(std::string_view alphabet, int length)
{
    std::random_device device;
    std::mt19937 engine{device()};
    std::uniform_int_distribution<> distribution{0, static_cast<int>(alphabet.length())-1};

    std::string password;
    password.reserve(length);

    std::generate_n(std::back_inserter(password), length, [&]() {
        return alphabet[distribution(engine)];
    });
    
    return password;
}

int main()
{
    while (true) {
        auto password{make_password("1234567890", 50)};
        std::cout << password << " " << password.capacity() << "\n";
        std::cin.get();
    }
    return 0;
}