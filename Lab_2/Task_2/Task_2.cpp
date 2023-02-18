/*
* 2.2. Индивидуальные задания
Написать программу обработки файла данных, состоящих из структур, в которой реализованы следующие функции: 
    стандартная обработка файла (создание, просмотр, добавление); 
    линейный поиск в файле; 
    сортировка массива (файла) методами прямого выбора и QuickSort; 
    двоичный поиск в отсортированном массиве.
* 
        13. В кассе хранится информация о поездах на ближайшую неделю: 
        - дата выезда, +
        - пункт назначения, +
        - время отправления, +
        - число свободных мест. 
        Необходимо зарезервировать m мест до города N на k-й день недели с временем отправления поезда не позднее t часов. 
        Вывести время отправления или сообщение о невозможности выполнить заказ. Ключ: число свободных мест.
*/
#include <iostream>
#include <fstream>
#include <time.h>

#define LENGHT_CHAR_ARRAY 10

using namespace std;

int GetRandomNumber(int min, int max);
void createFile();
void readFile();
void addTrainToFile();


char daysOfWeek[7][LENGHT_CHAR_ARRAY] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thirsday", "Friday", "Saturday" };
char cities[5][LENGHT_CHAR_ARRAY] = { "Misnk", "Mogilev", "Brest", "Vitebsk", "Grodno" };



struct Time {
    Time() {
        this->hour = GetRandomNumber(0, 23);
        this->minute = GetRandomNumber(0, 59);
    }
    Time(int hour, int minute) {
        this->hour = hour;
        this->minute = minute;
    }
    int hour{}, minute{};
};

struct Train {
    Train() {
        departureTime.hour = 0;
        departureTime.minute = 0;
        freeSpace = 0;
    }
    Train(bool) {
        departureTime = Time();
        strcpy_s(departureDate, daysOfWeek[GetRandomNumber(0, 6)]);
        strcpy_s(destination, cities[GetRandomNumber(0, 4)]);
        freeSpace = GetRandomNumber(0, 20);
        }
    Time departureTime;
    char departureDate[LENGHT_CHAR_ARRAY]{};
    char destination[LENGHT_CHAR_ARRAY]{};
    int freeSpace;
};


ostream& operator << (ostream& out, Time& time) {
    out << time.hour << ":" << time.minute;
    return out;
}

ostream& operator << (ostream& out, Train *train) {
    out << "Поезд направляется: " << train->destination << endl
        << "Отправляется в " << train->departureDate << endl
        << "Время отправления: " << train->departureTime << endl
        << "Колличество свободных мест: " << train->freeSpace << endl;
    return out;
}


int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    
    createFile();
    readFile();
    
}

void createFile(){ 
    struct  Train train = Train(true);
    int counter = 0;

    fstream outTrain("test", std::fstream::out | std::fstream::binary);
    if (!outTrain) {
        cerr << "Файл не создан\n";
        return;
    }
    cout << "Введите колличество добавляемых поездов:";
    cin >> counter;

    for (int i = 0; i < counter; i++) {
        train = Train(true);
        outTrain.write((char*)&train, sizeof(struct Train));
    }
    outTrain.close();
}

void readFile() {

    fstream inTrain("test", std::fstream::in | std::fstream::binary);
    if (!inTrain) {
        cout << "Нельзя открыть файл для чтения\n";
    }
    Train *rTrain = new Train();
    while (inTrain.read((char*)rTrain, sizeof(struct Train))) {
        cout << rTrain;
        //cout << rTrain->destination << endl << rTrain->departureDate << endl << rTrain->departureTime << endl;
        cout << endl;
    }

    inTrain.close();
}

void addTrainToFile() {

}

int GetRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}