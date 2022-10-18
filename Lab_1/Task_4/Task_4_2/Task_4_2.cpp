#include <iostream>
/*Для одномерного массива, состоящего из n значений (n – не больше 20),решить поставленную задачу. 
Предусмотреть ввод значений массива как с клавиатуры, так и с помощью заполнения случайными числами. 
Выводить сообщения в случае невозможности выполнения поставленного задания.

Вычислить произведение элементов массива, расположенных после
последнего нулевого элемента и не превышающих среднее арифметическое.
*/

using namespace std;

int getRandomNumber(int max, int min);
void printArray(int *array, int length);

#define LENGTH_ARRAY	50


int main() {
	int array[LENGTH_ARRAY];
	int length, answer = 1;
	int lastIndexZero = -1;
	int avarage = 0;
	
	do {
		cout << "Write lenght your array:";
		cin >> length;
	} while (length > LENGTH_ARRAY || length < 1);

	// Сделать выбор (автоматически или вручную) // ***переделать
	if (true) {
		for (int i = 0; i < length; i++) {
			array[i] = rand() % 10;
			if (array[i] == 0) {
				lastIndexZero = array[i];
			}
			avarage += array[i];
		}
	} else {
		cout << "Print numbers to your array";
		for (int i = 0; i < length; i++) {
			cin >> array[i];
			if (array[i] == 0) {
				lastIndexZero = array[i];
			}
			avarage += array[i];
		}
	}
	avarage /= length;
	printArray(array, length);

	if (lastIndexZero != -1 || lastIndexZero == length) {
		for (int i = lastIndexZero; i < length; i++) {
			if (array[i] <= avarage && array[i] != 0) {
				answer *= array[i];
			}
		}
		cout << "Avarage: " << avarage << endl;
		cout << "Answer is:" << answer << endl;
	} else {
		cout << "Ничего не получится";
	}

}

int getRandomNumber(int max, int min) {
	return min + rand() % max;
}

void printArray(int *array, int length) {
	for (int i = 0; i < length; i++) {
		cout << array[i] << " ";
	}
}