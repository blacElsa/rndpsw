#include <ctime>
#include <cstdio>
#include <random>
#include <string>
#include <iostream>
#include <algorithm>
#include <string_view>

#include <fmt/core.h>
#include <fmt/chrono.h>

#define PASSWORD_FILE_NAME "password.txt"

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

int create_password_file()
{
    auto file{std::fopen(PASSWORD_FILE_NAME, "w")};
    if (!file) return 0; // file open failed
    fmt::print(file, "{0:<32}|{1:^15}|{2:^10}\n", "Password", "Service", "Date");
    fmt::print(file, "{0:-^32}+{0:-^15}+{0:-^10}\n", "");
    std::fclose(file);
    return 1;
}

int write_password_to_file(std::string_view password, std::string_view service)
{
    auto file{std::fopen(PASSWORD_FILE_NAME, "a")};
    if (!file) return 0;
    fmt::print(file, "{0:<32}|{1:^15}|{2:%Y-%m-%d}\n", password, service, fmt::localtime(std::time(nullptr)));
    std::fclose(file);
    return 1;
}

int main()
{
    
    return 0;
}