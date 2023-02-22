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

#define LENGHT_CHAR_ARRAY 12
#define COUNT_DAYS 7
#define COUNT_CITIES 5

using namespace std;

int GetRandomNumber(int min, int max);
void createFile(char* name);
void readFile(char* name);
void addTrainToFile(char *name);


char daysOfWeek[COUNT_DAYS][LENGHT_CHAR_ARRAY] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
char cities[COUNT_CITIES][LENGHT_CHAR_ARRAY] = { "Минск", "Могилёв", "Брест", "Витебск", "Гродно" };



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
        departureTime = Time(0, 0);
    }
    Train(bool) {
        departureTime = Time();
        strcpy_s(departureDate, daysOfWeek[GetRandomNumber(0, COUNT_DAYS - 1)]);
        strcpy_s(destination, cities[GetRandomNumber(0, COUNT_CITIES - 1)]);
        freeSpace = GetRandomNumber(0, 20);
    }

    Time departureTime;
    char departureDate[LENGHT_CHAR_ARRAY]{};
    char destination[LENGHT_CHAR_ARRAY]{};
    int freeSpace{};
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
    system("chcp 1251");
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    char* name = new char;
    cin >> name;
    //createFile(name);
    //readFile(name);
    addTrainToFile(name);
    readFile(name);
    
}

void createFile(char* name){
    struct Train train = Train(true);
    int counter = 0;

    fstream outTrain(name, std::fstream::out | std::fstream::binary);
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

void readFile(char* name) {
    fstream inTrain(name, std::fstream::in | std::fstream::binary);
    if (!inTrain) {
        cerr << "Нельзя открыть файл для чтения\n";
        return;
    }
    Train *rTrain = new Train();
    while (inTrain.read((char*)rTrain, sizeof(struct Train))) {
        cout << rTrain;
        cout << endl;
    }
    delete rTrain;
    inTrain.close();
}

void addTrainToFile(char* name) {
    fstream addTrain(name,  std::fstream::app | std::fstream::out |std::fstream::binary);
    if (!addTrain) {
        cout << "Нельзя открыть файл для чтения\n";
        return;
    }
    auto train = new Train();
    cout << "Введите пункт назначения: ";
    cin >> train->destination;
    //strcpy_s(train->destination, temp);
    cout << "Введите день отправления:";
    cin >> train->departureDate;
    //strcpy_s(train->departureDate, temp);
    cout << "Введите время отправления";
    cin >> train->departureTime.hour;
    cin >> train->departureTime.minute;
    cout << "Введите количество свободных мест";
    cin >> train->freeSpace;

    addTrain.write((char*)train, sizeof(struct Train));
    addTrain.close();
    cout << "Добавлен поезд" << train << endl << endl;
}

int GetRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}