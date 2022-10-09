#include <iostream>
#include <cmath>

using namespace std;

double getDouble(string message);
int getInt();


int main() {
    double y, x, z, n, k, m;
    double fx = 0;
    int chooseFx;

    z = getDouble("z:");
    n = getDouble("n:");
    k = getDouble("k:");
    m = getDouble("m:");
    chooseFx = getInt();

    if (z > 1) {
        x = z;
        cout << "x = z\n";
    }
    else {
        x = (z * z) + 1;
        cout << "x = z2 + 1\n";
    }

    switch (chooseFx) {
        case 1: {
            fx = 2 * x;
            cout << "fx = 2x\n";
            break;
        }
        case 2: {
            fx = x * x;
            cout << "fx = x2\n";
            break;
        }
        case 3: {
            fx = x / 3;
            cout << "fx = x/3\n";
            break;
        }
    }

    y = sin(n * fx) + cos(k * x) + log10(m * x);

    if (y - y != 0) {
        cout << "You have problem with your numbers";
        return -1;
    }

    printf("Answer:\n%lf = sin(%.2lf * %.2lf) + cos(%.2lf * %.2lf) + ln(%.2lf * %.2lf)", y,n,fx,k,x,m,x);
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

int getInt() {
    int out;
    string message = "Write number from 1 to 3 :";

    while(true) {
        cout << message;
        while (!(cin >> out) || (cin.peek() != '\n')) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Is not a number" << endl << message;
        }
        if (out > 0 && out < 4) {
            return out;
        }
        cout << "Your number was wrong\n";
    }
}
