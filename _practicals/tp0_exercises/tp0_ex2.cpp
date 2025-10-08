#include <iostream>

// Exercise 0.2

int main() {
    int n;
    float y;

    // Documentation for std::cin and std::cout:
    // https://www.cppreference.com/w/cpp/io/basic_istream.html
    std::cout << "Type an integer and a float: " << std::endl;
    std::cin >> n >> y;

    std::cout << "The product of " << n << " with " << y << " is: " << n * y << std::endl;

    return 0;
}