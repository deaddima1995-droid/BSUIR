#include <iostream>
#include <math.h>

using namespace std;
double getDouble(string text);

int main() {
    double x, y, z, f;

    while (true) {
        x = getDouble("x:");
        y = getDouble("y:");
        z = getDouble("z:");

        f = (pow(y + pow(x - 1, 1.0 / 3), 1.0 / 4)) / (abs(x - y) * (pow(sin(z), 2) + tan(z)));

        if (f != f || f - f != 0) {
            printf("Your numbers was wrong, answer is %lf\nPlease try again\n", f);
            continue;
        }
        break;
    }
    printf("x = %lf\t y = %lf\t z = %lf\nAnswer = %lf", x, y, z, f);
}

double getDouble(string message) {

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