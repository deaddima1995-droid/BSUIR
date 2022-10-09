#include <iostream>
#include <cmath>
using namespace std;


/* Составить программу для определения значения y. 
Обязательно выводить сообщения о том, по какой ветви происходило вычисление значения переменной x
 y = sin(n*x) + cos(k*x) + ln(m*x), 
*/

int main() {
    double y, x, z, n, k, m;
    cout << "Write z:";
    cin >> z;
    cout << "Write n:";
    cin >> n;
    cout << "Write k:";
    cin >> k;
    cout << "Write m:";
    cin >> m;
    

    if (z > 1) {
        x = exp(z) + z;
        cout << "x = exp(z) + z\n";
    } else {
        x = (z * z) + 1;
        cout << "x = z2 + 1";
    }

    y = sin(n * x) + cos(k * x) + log10(m * x);

    printf("Answer : %lf", y);
}