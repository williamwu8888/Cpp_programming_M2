#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Exercise 4

// fstream, etc...      -> https://en.cppreference.com/w/cpp/io/basic_fstream
// basic_ios::openmode (fstream::in, fstream::out) 
//                      -> https://en.cppreference.com/w/cpp/io/ios_base/openmode
// ifstream::open       -> https://en.cppreference.com/w/cpp/io/basic_ifstream/open
// while (infile>>word) -> https://en.cppreference.com/w/cpp/io/basic_istream/operator_gtgt
// ofstream::open       -> https://en.cppreference.com/w/cpp/io/basic_ofstream/open
// cerr                 -> https://en.cppreference.com/w/cpp/io/cerr
// fstream::close       -> https://en.cppreference.com/w/cpp/io/basic_fstream/close
// getline              -> https://en.cppreference.com/w/cpp/string/basic_string/getline
// string::find         -> https://en.cppreference.com/w/cpp/string/basic_string/find

int main() {
    // Part 1: Count words in travail.txt
    {
        ifstream infile("tp0_files/file/travail.txt", ios::in);
        if (!infile) {
            cerr << "Error: cannot open travail.txt" << endl;
            return 1;
        }

        string word;
        int word_count = 0;

        // >> reads a single word delimited by space
        while (infile >> word) {
            ++word_count;
        }

        infile.close();
        cout << "Number of words in travail.txt: " << word_count << endl;
    }
    // Part 2: Copy names containing 'a' or 'A' from prenom.txt to lasnames_A.txt
    {
        ifstream input("tp0_files/file/prenom.txt", ios::in);
        ofstream output("tp0_files/file/lasnames_A.txt", ios::out);

        if (!input || !output) {
            cerr << "Error: cannot open prenom.txt or lasnames_A.txt" << endl;
            return 1;
        }

        string name;
        while (input >> name) {
            if (name.find('a') != string::npos || name.find('A') != string::npos) {
                output << name << '\n';
            }
        }

        // Close all streams
        input.close();
        output.close();

        cout << "Names containing 'a' copied to lasnames_A.txt" << endl;
    }

    return 0;
}
