#include <iostream>     // std::cout, std::cerr, std::endl      -> https://en.cppreference.com/w/cpp/header/iostream
#include <fstream>      // std::ifstream                        -> https://en.cppreference.com/w/cpp/io/basic_fstream
#include <sstream>      // std::istringstream                   -> https://en.cppreference.com/w/cpp/io/basic_istringstream
#include <vector>       // std::vector                          -> https://en.cppreference.com/w/cpp/container/vector
#include <string>       // std::string                          -> https://en.cppreference.com/w/cpp/string/basic_string

using namespace std;

int main() {
    string phrase, filename;

    cout << "Enter the phrase to display: ";
    getline(cin, phrase);

    cout << "Enter the filename of the ASCII art (without .txt): ";
    getline(cin, filename);
    string path = "tp0_files/file/" + filename + ".txt";

    istringstream iss(phrase); // https://en.cppreference.com/w/cpp/io/basic_istringstream
    string word;
    vector<string> lines; // https://en.cppreference.com/w/cpp/container/vector
    string current;

    // Split the phrase into lines of max 20 characters
    while (iss >> word) {      // https://en.cppreference.com/w/cpp/io/basic_istream/operator_gtgt
        if (current.empty()) { // https://en.cppreference.com/w/cpp/string/basic_string/empty
            if (word.length() > 20) { // https://en.cppreference.com/w/cpp/string/basic_string/length
                lines.push_back(word); // https://en.cppreference.com/w/cpp/container/vector/push_back
            } else {
                current = word;
            }
        } else if (current.length() + 1 + word.length() <= 20) {
            current += " " + word;
        } else {
            lines.push_back(current);
            if (word.length() > 20) {
                lines.push_back(word);
                current.clear();
            } else {
                current = word;
            }
        }
    }
    if (!current.empty()) lines.push_back(current);

    size_t width = 0; // https://en.cppreference.com/w/cpp/types/size_t
    for (const auto &line : lines) {
        if (line.length() > width) width = line.length();
    }

    // Display the phrase in a box
    cout << " " << string(width + 2, '_') << endl;
    for (const auto &line : lines) {
        cout << "| " << line << string(width - line.length(), ' ') << " |" << endl;
    }
    cout << " " << string(width + 2, '-') << endl;
    cout << " \\" << endl;
    cout << "  \\" << endl;

    // Read and display the ASCII art from the file
    ifstream file(path);
    if (!file) {
        cerr << "[Error] Could not open file: " << filename << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();

    return 0;
}
