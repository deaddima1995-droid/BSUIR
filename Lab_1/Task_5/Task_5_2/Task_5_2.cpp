/*
Написать программу по обработке двухмерного динамического массива. 
Размеры массива n, m и значения его элементов вводятся с клавиатуры.
В квадратной матрице найти максимальный среди элементов, лежащих ниже побочной диагонали.
*/

#include <iostream>

using namespace std;

int main() {
    int lines;
    int max = INT32_MIN;

    cout << "Print size of matrix:";
    cin >> lines;
    
    int** matrix = (int**)malloc(lines * sizeof(int*));
    for (int i = 0; i < lines; i++) {
        matrix[i] = (int*)malloc(lines * sizeof(int));
    }

    // Add number to array
    printf("Print your numbers from space matrix[%d][%d]\n", lines, lines);
    for (int i = 0; i < lines; i++) {
        for (int y = 0; y < lines; y++) {
            cin >> matrix[i][y];
        }
    }
    cout << endl;
    // Print array
    for (int i = 0; i < lines; i++) {
        for (int y = 0; y < lines; y++) {
            cout << matrix[i][y] << "\t";
        }
        cout << endl;
    }
    
    // Search max
    for (int i = 0; i < lines; i++) {
        for (int y = lines - i; y < lines; y++) {
            max = (matrix[i][y] > max) ?  matrix[i][y] : max;
        }
    }
    cout << "Max value:" << max << endl;
}

