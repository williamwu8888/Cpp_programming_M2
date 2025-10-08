#include <iostream>
#include <string>

// Exercice 0.1

int main() {
    // Documentation for std::cin and std::cout:
    // https://www.cppreference.com/w/cpp/io/basic_istream.html
    std::cout << "Comment vous appellez vous ? ";
    std::string name;
    std::cin >> name;
    std::cout << "Salut " << name << std::endl
                                        << "Et quel est le votre ? ";
    std::cin >> name;
    std::cout << "Enchante " << name << std::endl;
    return 0;
}