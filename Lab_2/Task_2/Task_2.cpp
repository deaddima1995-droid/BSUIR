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


#define OPTION_CREATING  ios::out |ios::trunc | ios::binary
#define OPTION_READING ios::binary
#define OPTION_WRIATING ios::binary


using namespace std;

int GetRandomNumber(int min, int max);

char month[3][10] = { "January", "February", "March" };

string daysOfWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thirsday", "Friday", "Saturday" };
string cities[5] = { "Misnk", "Mogilev", "Brest", "Vitebsk", "Grodno"};


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
    /*
    * Строки нельзя т.к нету велечины занимаемой памяти
    Train() {
        this->departureTime = new Time();
        this->departureDate = daysOfWeek[GetRandomNumber(0, 6)];
        this->destination = cities[GetRandomNumber(0,4)];
        this->freeSpace = GetRandomNumber(0, 10);
    }
    Train(Time* departureTime, string departureDate, string destination, int freeSpace) {
        this->departureTime = departureTime;
        this->departureDate = departureDate;
        this->destination = destination;
        this->freeSpace = freeSpace;
    }
    Time *departureTime;
    */
    Train(int space) {
        this->freeSpace = space;
    }
    char departureDate[10];
    Time *departureTime{};
    int freeSpace;
};

Train** getTrains();
void createFile(char* name);
void readFile(char* name);
void addTrainToFile();



int main() {

    srand(time(NULL));
    fstream file;

    Train* in = new Train(55);
    in->freeSpace = 56;
    cin >> in->departureDate;

    file.open("test", fstream::out | fstream::binary);
    file.write((char*)&in, sizeof(Train));
    file.close();

    Train* out{};
    file.open("test", fstream::in | fstream::binary);
    file.read((char*)&out, sizeof(Train));
    cout << "File was created\n";
    file.close();

    cout << "Free space - " << out->freeSpace << endl;
    cout << "Desteny - " << out->departureDate << endl;
}

Train** getTrains()
{
    return nullptr;
}

void createFile(char* name){ 
    /*
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
    */
}

void readFile(char* name) {
    /*
    fstream file;
    file.open("test", fstream::out | fstream::binary);
    if (!file.is_open()) {
        system("cls");
        cerr << "Error, " << name << " file can't create\n";
        return;
    }
    Train* temp = new Train();
    file.write((char*)&temp, sizeof(Train));
    file.close();

    Train* out{};
    file.open("test", fstream::in | fstream::binary);
    file.read((char*)&out->freeSpace, sizeof(out->freeSpace));
    int count = 0;
   
        count++;

    
    cout << "File " << name << " was created\n";
    file.close();
    cout << "Число поездов в файле - " << count << endl;
    cout << "Free space - " << out->freeSpace << endl;
    */
}

void addTrainToFile() {
}

int GetRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}
