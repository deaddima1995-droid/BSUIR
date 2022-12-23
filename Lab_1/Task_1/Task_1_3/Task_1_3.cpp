#include <iostream>
#include <cmath>

using namespace std;
double getNumber(string message);

int main() {
    double x, y, z, f;

    while (true) {
        x = getNumber("x:");
        y = getNumber("y:");
        z = getNumber("z:");

        f = (pow(y + pow(x - 1, 1.0 / 3), 1.0 / 4)) / (fabs(x - y) * (pow(sin(z), 2) + tan(z)));

        if (f - f != 0) {
            printf("Your numbers was wrong, answer is %lf\nPlease try again\n", f);
            continue;
        }
        break;
    } 
    printf("x = %lf\t y = %lf\t z = %lf\nAnswer = %lf", x, y, z, f);
    system("pause");
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