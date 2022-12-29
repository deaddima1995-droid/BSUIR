#include <iostream>
#include <cmath>

using namespace std;

double factorial(double number);

int main() {
    double a, b, h, sX, yX;
    int n;

    /*
    a = 0.1;
    b = 1.0;
    h = 0.1;
    n = 5;
    */
    cout << "Write a:";
    cin >> a;
    cout << "Write b:";
    cin >> b;
    cout << "Write h:";
    cin >> h;
    cout << "Write n:";
    cin >> n;

    for (double x = a; x <= b; x += h) {
        sX = 0;
        yX = 2 * (pow(cos(x), 2) - 1);
        
        for (double k = 1; k <= n; k++) {
            sX += pow(-1, k) * (pow(2 * x,2 * k) / factorial(2 * k));
        }
        printf("%.6lf\t%.6lf\tdelta %lf\n",yX,sX,fabs(sX - yX));
    }
}

double factorial(double number) {
    if (number == 0) {
        return 1;
    }
    return number * factorial(number - 1);
}
