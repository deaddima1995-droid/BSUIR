/*
13. Вычислить y = xn по следующему правилу: 
y = ( x^(n/2) )2, если n четное, 
и 
y = x * y^(n-1), если n нечетное.
*/


#include <iostream>
#include <cmath>

using namespace std;

int degree(int x, int n);

int main() {
    cout << "Hello World!\n";
}

int degree(int x, int n) {
    if (n == 0) return 1;

    if (n % 2 == 0 || n != 0) {
        return (pow(pow(x, n / 2), 2));
    } else {

    }
    return 0;
}
