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


#define OPTION_CREATING  ios::out |ios::trunc | ios::binary
#define OPTION_READING ios::binary
#define OPTION_WRIATING ios::binary


using namespace std;



struct Time {
    Time() {}
    Time(int hour, int minute) {
        this->hour = hour;
        this->minute = minute;
    }
    int hour, minute;
};


struct Train {
    Time departureTime{};
    int departureDate{};
    char destination[15];
    uint32_t freeSpace{};
};

Train** getTrains();
void createFile(char* name);
void readFile(char* name);
void addTrainToFile();



int main() {

    //ofstream out;
    //out.open("cash.bin", OPTION_CREATING);
    cout << "Hello World!\n";
    char name[9];
    cin >> name;
    createFile(name);
}

Train** getTrains()
{
    return nullptr;
}

void createFile(char* name){ 
    ofstream file;
    file.open(name, OPTION_CREATING);
    if (!file.is_open()) {
        system("cls");
        cerr << "Error, " << name << " file can't create\n";
        return;
    }
    int count = 0;
    cout << "Write count of trains:";
    cin >> count;
    for (int i = 0; i < count; i++) {
        Train *temp = new Train();
        file << temp;
    }
    cout << "File " << name << " was created\n";
    file.close();
}

void readFile(char* name) {
    
}

void addTrainToFile()
{
}
