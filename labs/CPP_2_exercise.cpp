#include <iostream>
using namespace std;

class DoubleArray {
    double _a[5] ;
public:
    DoubleArray() { for(int i=0; i<5; i++) { _a[i]=i ; } } ;
    DoubleArray(const DoubleArray& d) {
        for (int i=0; i<5; i++) { _a[i] = d._a[i]; }
    }
    void display() {for(int i=0; i<5 ; i++) {cout << "a[" << i << "] = " << _a[i] << endl;}};
};

int main() {
    DoubleArray a;
    DoubleArray b(a);
    a.display();
    b.display();
}