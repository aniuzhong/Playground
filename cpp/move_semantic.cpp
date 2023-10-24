#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;
#define type_to_string(x) type_id_with_cvr<decltype(x)>().pretty_name().c_str()

int main() {
    std::string str, str1, str2;
    std::vector<int>::iterator it;

    // a function call or an overloaded operator expression,
    // whose return type is lvalue reference, is LVALUE.

    std::cout << type_to_string(std::cout << 1) << '\n';
    std::cout << type_to_string(std::getline(std::cin, str)) << '\n';
    std::cout << type_to_string(str1 = str2);
    std::cout << type_to_string(++it);

    std::cout << '\n';

    // a function call or an overloaded operator expression,
    // whose return type is non-reference, is PRVALUE

    std::cout << type_to_string(str.substr(111, 222)) << '\n';
    std::cout << type_to_string(str1 + str2) << '\n';
    std::cout << type_to_string(it++) << '\n';

    std::cout << '\n';

    // a function call or an overloaded operator expression,
    // whose return type is rvalue reference, is XVALUE

    int x = 42;
    std::cout << type_to_string(std::move(x)) << '\n';
}