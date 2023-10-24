// copy from https://en.cppreference.com/w/cpp/language/enum

#include <iostream>

int main() {
    enum class Color { red, green = 20, blue };
    Color r = Color::blue;

    switch (r) {
    case Color::red:
        std::cout << "red\n";
        break;
    case Color::green:
        std::cout << "green\n";
        break;
    case Color::blue:
        std::cout << "blue\n";
        break;
    }

    // int n = r; error: no implicit conversion from scoped enum to int
    int n = static_cast<int>(r); // OK, n = 21
    std::cout << n << '\n';
}