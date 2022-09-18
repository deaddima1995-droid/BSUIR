#include <iostream>

/* Составить программу для расчёта заданных выражений с проверкой исключительных ситуаций: 
        деление на нуль, вычисление корня из отрицательного числа и т. п. При вводе данных использовать проверку на ввод нечисловых данных.
        z1 = cosA + sinA + cos3A + sin 3A
        z2 = 2 * sqrt(2) * cosA * sin(pi/4 + 2 * A);
*/
using namespace std;

int main() {
    const double pi = 3.1415926;
    double z1, z2;
    double angleAlpha;
     
    
    printf_s("Write angle Alpha in Radian:");
    /*
    while (1) {
        cin >> angleAlpha;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You didn't enter a number" << endl;
            cout << "Write again: ";
        } else {
            break;
        }
    } 
    */

    angleAlpha = 180 / pi * angleAlpha;
    printf("Angle Alpha degree : % lf\n", angleAlpha);
    
    // Деление на нуль невозможно, вычисление корня из отрицательного числа невозможно. Проверка не требуется исходя из задания.
    z1 = cos(angleAlpha) + sin(angleAlpha) + cos(3 * angleAlpha) + sin(3 * angleAlpha);
    z2 = 2 * sqrt(2) * cos(angleAlpha) * sin(pi / 4 + 2 * angleAlpha);

    printf("Answer:\nz1 = %f\nz2 = %f", z1, z2);
}
bool isNumber(char line[]) {
    
    return 0;
}