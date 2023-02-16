﻿/*
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


#define OPTION_READING fstream::in | fstream::binary
#define OPTION_WRIATING fstream::out | fstream::binary
#define LENGHT_CHAR_ARRAY 10


using namespace std;

int GetRandomNumber(int min, int max);

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
        this->departureTime = Time(0,0);
        this->freeSpace = 0;
    }
    Train(bool) {
        this->departureTime = Time();
        memcpy(this->departureDate, cities[GetRandomNumber(0, 6)], sizeof(this->departureDate));
        memcpy(this->destination, cities[GetRandomNumber(0, 4)], sizeof(this->destination));
        this->freeSpace = GetRandomNumber(0, 20);
    }
    
    Time departureTime;
    char departureDate[LENGHT_CHAR_ARRAY]{};
    char destination[LENGHT_CHAR_ARRAY]{};
    int freeSpace{};
};

Train** getTrains();
void createFile(char* name);
void readFile(char* name);
void addTrainToFile();

FILE *file;

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    char* name{};
    cout << "Имя файла:";
    cin >> name;
    createFile(name);
    cout << "\n";
    readFile(name);

}

Train** getTrains()
{
    return nullptr;
}

void createFile(char* name){ 
    fstream file;
    
    file.open(name, OPTION_WRIATING);
    if (!file.is_open()) {
        cerr << "Файл не открыт";
        return;
    }
    for (int i = 0; i < 10; i++) {
        Train* temp = new Train(true);
        file.write((char*)&temp, sizeof(Train));
        cout << "Поезд направляется - " << temp->destination
            << " в " << temp->departureDate
            << " \n\tВремя отправления " << temp->departureTime.hour << ":" << temp->departureTime.minute
            << "\n\tКолличество свободных мест - " << temp->freeSpace << endl;
    }

    file.close();
}

void readFile(char* name) {
    fstream file;
    Train* temp = new Train();
    file.open(name, OPTION_READING);
    if (!file.is_open()) {
        cerr << "Файл не открыт";
        return;
    }
    while (file.read((char*)&temp, sizeof(Train))) {
        cout << "Поезд направляется - " << temp->destination
            << " в " << temp->departureDate
            << " \n\tВремя отправления " << temp->departureTime.hour << ":" << temp->departureTime.minute
            << "\n\tКолличество свободных мест - " << temp->freeSpace << endl;
    }
    
    file.close();
}

void addTrainToFile() {

}

int GetRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

/*OLD
char* fileName = new char[10];
    cin >> fileName;



    if (fopen_s(&file, fileName, OPTION_WRIATING) == NULL) {
        auto* temp = new Train();

        for (int i = 0; i < 10; i++)
        {
            fwrite(temp, sizeof(struct Train), 1, file);
            temp = new Train;
        }
    }
    fclose(file);

    fopen_s(&file, fileName, "rb");
    if (file == nullptr) {
        system("cls");
        cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << fileName << "\033[0m" << endl;
        return 0;
    }

    auto* out = new Train;
    while (fread(out, sizeof(struct Train), 1, file)) {
        cout << "Train -" << out->destination << " space -" << out->freeSpace << "\tTime" << out->departureTime.hour << endl;
    }


*/