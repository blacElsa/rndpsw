#include <ctime>
#include <cstdio>
#include <random>
#include <string>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <string_view>

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/ostream.h>

#include <boost/program_options.hpp>

class PasswordGenerator {
public:
    PasswordGenerator(const std::string& alphabet, int length)
        : _alphabet{alphabet}, _length{length} {
        std::random_device device;
        _engine.seed(device());
        _distribution = std::uniform_int_distribution<>(0, static_cast<int>(_alphabet.length())-1);
    }

    PasswordGenerator()
        : PasswordGenerator(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890", 13
        ) { }

    std::string operator()() {
        std::string password;
        password.reserve(_length);

        std::generate_n(std::back_inserter(password), _length, [this]() {
            return _alphabet[_distribution(_engine)];
        });

        return password;
    }
private:
    int _length;
    std::string _alphabet;
    std::mt19937 _engine;
    std::uniform_int_distribution<> _distribution;
};

class PasswordFile {
public:
    PasswordFile(const std::string& file_name) {
        namespace fs = std::filesystem;
        if (!fs::exists(file_name)) {
            _file = std::fopen(file_name.c_str(), "w");
            fmt::print(_file, "{0:<32}|{1:^15}|{2:^10}\n", "Password", "Service", "Date");
            fmt::print(_file, "{0:-^32}+{0:-^15}+{0:-^10}\n", "");
        }
        else {
            _file = std::fopen(file_name.c_str(), "a");
        }
    }

    ~PasswordFile() {
        std::fclose(_file);
    }

    void write(std::string_view password, std::string_view service) {
        fmt::print(_file, "{:<32}|{:^15}|{:%Y-%m-%d}\n", password, service, fmt::localtime(std::time(nullptr)));
    }
private:
    FILE* _file;
};

int main(int argc, char** argv)
{
    namespace opt = boost::program_options;
    std::string mode;

    opt::options_description general_desc("Password generator");
    general_desc.add_options()
        ("help,h", "Show help message")
        ("mode", opt::value<std::string>(&mode), "Select mode: auto/manual");
    
    opt::options_description auto_mode_desc("Auto mode options");
    auto_mode_desc.add_options()
        ("service,s", opt::value<std::string>()->default_value("undef"), "Service name");
    
    opt::options_description manual_mode_desc("Manual mode options");
    manual_mode_desc.add_options()
        ("service,s", opt::value<std::string>()->default_value("undef"), "Service name")
        ("len", opt::value<int>(), "Password length")
        ("numbers,n", "Allow numbers in alphabet")
        ("lower,l", "Allow lower symbols")
        ("alpha,a", "Allow alpha symbols")
        ("extra,e", "Allow special symbols");

    opt::variables_map vm;

    auto parsed = opt::command_line_parser(argc, argv)
        .options(general_desc).allow_unregistered().run();
    opt::store(parsed, vm);
    opt::notify(vm);

    try {
        if (mode == "auto") {

        }
        else if (mode == "manual") {

        }
        else {
            general_desc.add(auto_mode_desc).add(manual_mode_desc);
            fmt::print("{}\n", general_desc);
        }
    }
    catch (...) {
        fmt::print("{}\n", general_desc);
    }

    return 0;
}