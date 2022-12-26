#include <iostream>
/*Для одномерного массива, состоящего из n значений (n – не больше 20),решить поставленную задачу. 
Предусмотреть ввод значений массива как с клавиатуры, так и с помощью заполнения случайными числами. 
Выводить сообщения в случае невозможности выполнения поставленного задания.

Вычислить произведение элементов массива, расположенных после
последнего нулевого элемента и не превышающих среднее арифметическое.
*/ 

using namespace std;

#define LENGTH_ARRAY	20

int main() {
	
	int length;
	int lastIndexZero = -1;
	double average = 0.0, answer = 1.0;
	char choise;

	
	do {
		cout << "Write length your array:\t";
		cin >> length;
	} while (length > LENGTH_ARRAY || length < 1);

	cout << "You want add numbers to array automatic?(Y/N):\t";
	cin >> choise;

	auto *array = new int[LENGTH_ARRAY]{};

	if (choise == 'Y' || choise == 'y') {
		for (int i = 0; i < length; i++) {
			array[i] = -1 + rand() % 10;
			cout << array[i] << " ";
			if (array[i] == 0) {
				lastIndexZero = i;
			}
			average += (double) array[i];
		}
	} else {
		cout << "Print numbers to your array with space:\n";
		for (int i = 0; i < length; i++) {
			cin >> array[i];
			cout << array[i] << " ";
			if (array[i] == 0) {
				lastIndexZero = i;
			}
			average += array[i];
		}
	}
	average /= (double)length;
	cout << endl;

	if (lastIndexZero > -1 && lastIndexZero + 1 < length) {
		for (int i = lastIndexZero + 1; i < length; i++) {
			if ((double)array[i] <= average) {
				answer *= array[i];
			}
		}
		cout << "Last index of Zero:" << lastIndexZero << endl;
		cout << "Average: " << average << endl;
		cout << "Answer is:" << answer << endl;
	} else if (lastIndexZero + 1 == length) {
		cout << "Zero was last";
	} else {
		cout << "Array has not zero";
	}
	delete[] array;
}