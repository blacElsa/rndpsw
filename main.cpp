#include <random>
#include <string>
#include <iostream>
#include <algorithm>
#include <string_view>

#include <fmt/core.h>

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
        auto password{make_password("1234567890", 4)};
        std::cout << fmt::format("{}\n", password);
        std::cin.get();
    }
    return 0;
}