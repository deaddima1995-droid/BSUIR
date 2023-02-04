/*
13. Вычислить y = x^n по следующему правилу: 
y = ( x^(n/2) )2, если n четное, 
и 
y = x * y^(n-1), если n нечетное.
*/


#include <iostream>
#include <cmath>

using namespace std;

int degree(int x, int n);

int main() {
    cout << "Answer: " << degree(2,10);
}

int degree(int x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x;

    if (n % 2 == 0) {
        return pow(degree(x, n / 2), 2);
    }
    return x * degree(x, n - 1);
}
