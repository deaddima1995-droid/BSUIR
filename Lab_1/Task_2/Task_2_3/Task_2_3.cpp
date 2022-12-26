#include <iostream>
#include <cmath>
   /*
   Составить программу нахождения требуемого значения с указанными исходными данными.
   Поиск минимального и максимального значения элементов организовать в виде отдельной функции.
   При вводе данных использовать проверку на ввод не числовых данных.
   Организовать проверку исключительных ситуаций.
   */

using namespace std;

double getMax(double x, double y);
double getMin(double x, double y);
double getNumber(string message);

int main() {
    double x, y, F;
    x = getNumber("x:");
    y = getNumber("y:");

    if (fabs(x) + fabs(y) <= 1 || x >= 0) {
        F = getMax(x, y) + sqrt(x);
        printf("%.2lf = max(%.2lf,%.2lf) + sqrt(%.2lf)", F, x, y, x);
    } else if (fabs(x) + fabs(y) > 0 || (x < 0 && y < 0)) {
        F = getMin(x, y) + pow(sin(x), 2) - cos(y * y);
        printf("%.2lf = min(%.2lf,%.2lf) + sin^2(%.2lf) - cos(%.2lf)^2",F, x, y, x, y);
    } else {
        F = exp(x * x + fabs(y));
        printf("%.2lf = e^%.2lf&2 + |%.2lf|", F, x, y);
    }

    if (F - F != 0) {
        printf("Error");
    }
}

double getMax(double x, double y) {
    return (x > y)? x : y;
}

double getMin(double x, double y) {
    return (x < y)? x : y;
}

double getNumber(string message) {
    double out;
    message = "Write " + message;

    cout << message;
    while (!(cin >> out) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Is not a number" << endl << message;
    }
    return out;
}
