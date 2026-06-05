// MentalArithmeticTrainer.cpp: 应用程序
//

#include "version.h"

#include <iostream>
#include <string>
#include <limits>
#include <concepts>
#include <random>
#include <cstdint>
#include <optional>

constexpr char nextl = '\n';

template <typename T>
concept Streamable = requires(std::istream & is, T & v) {
    is >> v;
};

template <Streamable T, typename Pred>
    requires std::predicate<Pred&, const T&>
T get_stdin(const std::string& message, Pred&& condition) {
    T val;
    while (true) {
        std::cout << message;
        std::cin >> val;

        if (std::cin.eof()) {
            std::cout << "输入结束，退出程序。\n";
            std::exit(0);
        }

        bool failed = std::cin.fail();
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (failed) {
            std::cout << "输入不合法! 请重试.\n";
            continue;
        }
        if (condition(val)) {
            return val;
        }
        std::cout << " ! 输入错误值，请重新输入.\n";
    }
}

uint64_t pow10(uint64_t exp);

int main()
{
    using std::cout, std::cin;

    cout << "----- 自动口算训练器 " << VERSION_STRING << " -----"  << nextl << nextl;

    std::random_device rd;
    std::mt19937 mt(rd());
    
    bool running = true;
    while (running) {
        uint64_t max_digital_x = 0;
        uint64_t min_digital_x = 0;
        uint64_t max_digital_y = 0;
        uint64_t min_digital_y = 0;

        uint64_t max_digital = 5;

        auto check_digital = [max_digital](uint64_t val) { return val <= max_digital; };

        max_digital_x = get_stdin<uint64_t>("请输入乘数1的最大位数(1-5): ", check_digital);
        min_digital_x = get_stdin<uint64_t>("请输入乘数1的最小位数(1-5): ", [max_digital_x](uint64_t val) { return 0 < val && val <= max_digital_x; });
        max_digital_y = get_stdin<uint64_t>("请输入乘数2的最大位数(1-5): ", check_digital);
        min_digital_y = get_stdin<uint64_t>("请输入乘数2的最小位数(1-5): ", [max_digital_y](uint64_t val) { return 0 < val && val <= max_digital_y; });
        uint64_t count = get_stdin<uint64_t>("请输入生成的练习数: ", [](uint64_t val) { return val > 0; });

        uint64_t min_x = pow10(min_digital_x - 1);
        uint64_t max_x = pow10(max_digital_x) - 1;
        uint64_t min_y = pow10(min_digital_y - 1);
        uint64_t max_y = pow10(max_digital_y) - 1;

        std::uniform_int_distribution<uint64_t> x_dist(min_x, max_x);
        std::uniform_int_distribution<uint64_t> y_dist(min_y, max_y);

        for (uint64_t i = 0; i < count; i++) {
            cout << " * 练习 " << i + 1 << "/" << count << "\n\n";
            uint64_t x = x_dist(mt);
            uint64_t y = y_dist(mt);
            uint64_t result = x * y;

            get_stdin<uint64_t>(std::to_string(x) + " x " + std::to_string(y) + " = ", [result](uint64_t val) { return val == result; });
            cout << "正确!\n\n";
        }

        char choice = get_stdin<char>("继续吗? (Y/N): ", [](char val) { return val == 'Y' || val == 'y' || val == 'N' || val == 'n'; });
        running = choice == 'Y' || choice == 'y';
    }

    return 0;
}

uint64_t pow10(uint64_t exp) {
    uint64_t res = 1;
    for (uint64_t i = 0; i < exp; ++i) res *= 10;
    return res;
};
