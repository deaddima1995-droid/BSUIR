#include <iostream>
#include <math.h>

/* Составить программу для расчёта заданных выражений с проверкой исключительных ситуаций: 
        деление на нуль, вычисление корня из отрицательного числа и т. п. При вводе данных использовать проверку на ввод нечисловых данных.
        z1 = cosA + sinA + cos3A + sin 3A
        z2 = 2 * sqrt(2) * cosA * sin(pi/4 + 2 * A);
*/
using namespace std;

int main() {
    const double pi = 3.1415926;
    double z1, z2;
    double angleRadian,angleDegree;
    
    cout << "Write angle Alpha in Radian:";

    // Проверка на число
    while (!(cin >> angleRadian) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Is not a number" << endl << "Please try again:";
    }

    angleDegree = 180 / pi * angleRadian;
    printf("Angle Alpha degree : % lf\n", angleRadian);
    
    z1 = cos(angleRadian) + sin(angleRadian) + cos(3 * angleRadian) + sin(3 * angleRadian);
    z2 = 2 * sqrt(2) * cos(angleRadian) * sin(pi / 4 + 2 * angleRadian);

    printf("Answer:\nz1 = %f\nz2 = %f", z1, z2);
    
}