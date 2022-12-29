/* На основании задания, размещенного в п. 3.3.2, написать программу рас-
чета выбранной функции Y(x), S(x) или |Y(x) – S(x)|, вид которой, в свою оче-
редь, передается в качестве параметра в функцию вывода (Out_Rez).*/
#include <iostream>

using namespace std;

void Out_Rez(double function(double x), double a, double b, double h);
double fun_sX(double x);
double fun_sY(double x);
double factorial(double number);

int main() {
    Out_Rez(fun_sX, 0.1, 1, 0.1);
    cout << endl;
    Out_Rez(fun_sY, 0.1, 1, 0.1);
}

void Out_Rez(double function(double x), double a, double b, double h) {
    for (double x = a; x <= b; x+= h) {
        cout << "x = " << function(x) << endl;
    }
}

double fun_sX(double x) {
    double sX{};
    for (int k = 1; k < 5; k++) {
        sX += pow(-1, k) * (pow(2 * x, 2 * k) / factorial(2 * k));
    }
    return sX;
}

double fun_sY(double x) {
    return 2 * (pow(cos(x), 2) - 1);;
}

double factorial(double number) {
    if (number == 0) {
        return 1;
    }
    return number * factorial(number - 1);
}