#include <boost/type_index.hpp>
#include <cstdio>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using boost::typeindex::type_id_with_cvr;
#define type_to_string(x) type_id_with_cvr<decltype(x)>().pretty_name().c_str()

// T: decltype((expression))
template <typename T>
constexpr inline bool is_lvalue = std::is_lvalue_reference_v<T>;

template <typename T>
constexpr inline bool is_xvalue = std::is_rvalue_reference_v<T>;

template <typename T>
constexpr inline bool is_prvalue = !(is_lvalue<T> || is_xvalue<T>);

// template <typename T>
// std::string type_to_string() {
//     std::string type_name{__PRETTY_FUNCTION__};  // std::string type_to_string() [with T = int&&; ...]
//     auto start_pos = type_name.find_first_of('=') + 2;
//     auto end_pos = type_name.find_first_of(';', start_pos);
//     return type_name.substr(start_pos, end_pos - start_pos);
// }

// When parameter is reference，compiler will
// select overload according to the value category of the para expression
void f(int&&) { std::cout << "choosing f(int&&)\n"; }
void f(int&) { std::cout << "choosing f(int&)\n"; }
// can't define void f(int)

void always_lvalue(int&& a) {
    std::cout << std::boolalpha;
    std::cout << "The type of a: " << type_id_with_cvr<decltype(a)>() << '\n';
    std::cout << "The value catogory of a: " << type_id_with_cvr<decltype((a))>() << '\n';
    std::cout << "The value catogory of a is lvalue: " << type_id_with_cvr<decltype((a))>() << '\n';
    f(a);
}

template <typename T>
void perfect_forwarding(T&& a) {
    // std::cout << std::boolalpha;
    std::cout << "T was deduced as: " << type_id_with_cvr<T>() << '\n';
    std::cout << "The type of a: " << type_id_with_cvr<decltype(a)>() << '\n';
    std::cout << "The value category of a: " << type_id_with_cvr<decltype((a))>() << '\n';
    std::cout << "The value category of static_cast<decltype(a)>(a): " << type_id_with_cvr<decltype((static_cast<decltype(a)>(a)))>() << '\n';
    std::cout << "The value category of std::forward<T>(a): " << type_id_with_cvr<decltype((std::forward<T>(a)))>() << '\n';

    f(std::forward<T>(a));
}

int main() {
    int x = 42;
    // [1] When parameter is reference，compiler will
    // select overload according to the value category of the para expression
    f(x);             // param is lvalue, choose f(int&)
    f(std::move(x));  // param is rvalue, choose f(int&&)

    // [2] No matter the what value category the parameter is,
    // argument's value categor  will always be lvalue
    always_lvalue(std::move(x));
    std::cout << '\n';

    // [3] Passing std::forward<T>(a) instead of a 
    perfect_forwarding(std::move(x));
    std::cout << '\n';
    perfect_forwarding(x);
}