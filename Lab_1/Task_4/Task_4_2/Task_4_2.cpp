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
	int array[LENGTH_ARRAY];
	int length, answer = 1;
	int lastIndexZero = -1;
	float avarage = 0.0;
	char choise;

	
	do {
		cout << "Write lenght your array:\t";
		cin >> length;
	} while (length > LENGTH_ARRAY || length < 1);

	cout << "You want add numbers to array automatic?(Y/N):\t";
	cin >> choise;

	if (choise == 'Y' || choise == 'y') {
		for (int i = 0; i < length; i++) {
			array[i] = -1 + rand() % 10;
			cout << array[i] << " ";
			if (array[i] == 0) {
				lastIndexZero = i;
			}
			avarage += array[i];
		}
	} else {
		cout << "Print numbers to your array with space:\n";
		for (int i = 0; i < length; i++) {
			cin >> array[i];
			cout << array[i] << " ";
			if (array[i] == 0) {
				lastIndexZero = i;
			}
			avarage += array[i];
		}
	}
	avarage /= length;
	cout << endl;

	if (lastIndexZero != -1 && lastIndexZero + 1 < length) {
		for (int i = lastIndexZero + 1; i < length; i++) {
			if ((float)array[i] <= avarage) {
				answer *= array[i];
			}
		}
		cout << "Last index of Zero:" << lastIndexZero << endl;
		cout << "Avarage: " << avarage << endl;
		cout << "Answer is:" << answer << endl;
	} else if (lastIndexZero + 1 == length) {
		cout << "Zero was last";
	} else {
		cout << "Array has not zero";
	}

}