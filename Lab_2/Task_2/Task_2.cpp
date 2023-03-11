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

        Двоичный поиск
int binarySearch(int[] arr, int key) {
    int low = 0;
    int high = arr.length - 1;

    while (low <= high) {
        int mid = (low + high) >>> 1;
        int midVal = arr[mid];

        if (midVal < key)
            low = mid + 1;
        else if (midVal > key)
            high = mid - 1;
        else
            return mid; // key found
    }
    return -(low + 1);  // key not found.
}



*/

#include <iostream>
#include <fstream>
#include <time.h>

#define LENGHT_CHAR_ARRAY 12
#define COUNT_DAYS 7
#define COUNT_CITIES 5
#define COUNT_FREE_SPACE 20

using namespace std;

char daysOfWeek[COUNT_DAYS][LENGHT_CHAR_ARRAY] = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
char cities[COUNT_CITIES][LENGHT_CHAR_ARRAY] = { "Минск", "Могилёв", "Брест", "Витебск", "Гродно" };


struct Time {
    Time() {
        this->hour = 0;
        this->minute = 0;
    }
    Time(int hour, int minute) {
        this->hour = hour;
        this->minute = minute;
    }
    int hour, minute;
};

struct Train {
    Train() {
        this->departureTime = Time();
        this->freeSpace = 0;
    }
    Train(int hour, int minute, int date, int destiny, int freeSpace) {
        this->departureTime.hour = hour;
        this->departureTime.minute = minute;
        strcpy_s(this->departureDate, daysOfWeek[date]);
        strcpy_s(this->destination, cities[destiny]);
        this->freeSpace = freeSpace;
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

void createFile(char* name);
void readFile(char* name);
void addTrainToFile(char* name);
bool linearSerach(Train *tTemp, int key);
int getRandomNumber(int min, int max);
Train* getRandomTrain();


int main() {
    system("chcp 1251");
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    char* name = new char;
    cin >> name;
    createFile(name);
    readFile(name);
    addTrainToFile(name);
    readFile(name);
    
}

void createFile(char* name){
    Train* train = new Train();
    int counter = 0;

    fstream outTrain(name, std::fstream::out | std::fstream::binary);
    if (!outTrain) {
        cerr << "Файл не создан\n";
        return;
    }
    cout << "Введите колличество добавляемых поездов:";
    cin >> counter;

    for (int i = 0; i < counter; i++) {
        train = getRandomTrain();
        outTrain.write((char*)train, sizeof(struct Train));
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
    cout << "Введите день отправления:";
    cin >> train->departureDate;
    cout << "Введите время отправления";
    cin >> train->departureTime.hour;
    cin >> train->departureTime.minute;
    cout << "Введите количество свободных мест";
    cin >> train->freeSpace;

    addTrain.write((char*)train, sizeof(struct Train));
    addTrain.close();
    cout << "Добавлен поезд" << train << endl << endl;
}

bool linearSerach(Train* tTemp, int key) {
    if (tTemp->freeSpace == key) {
        return true;
    }
    return false;
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

Train* getRandomTrain() {
    return new Train(getRandomNumber(0, 23),
                     getRandomNumber(0, 59),
                     getRandomNumber(0,COUNT_DAYS - 1),
                     getRandomNumber(0, COUNT_CITIES - 1),
                     getRandomNumber(0, COUNT_FREE_SPACE));
}