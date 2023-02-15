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

 char daysOfWeek[7][10] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thirsday", "Friday", "Saturday" };
 char cities[5][10] = { "Misnk", "Mogilev", "Brest", "Vitebsk", "Grodno" };



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
    

    Time *departureTime;
    //char departureDate[10];
    char destination[10]; 
    int freeSpace;
};

Train** getTrains();
void createFile(char* name);
void readFile(char* name);
void addTrainToFile();

FILE *file;

int main() {
    char* fileName = new char[10];
    cin >> fileName;



    if (fopen_s(&file, fileName, "wb+") == NULL) {
        auto* temp = new Train;
        temp->freeSpace = GetRandomNumber(0, 10);
        temp->departureTime = new Time();
        memcpy(temp->destination, cities[GetRandomNumber(0, 4)], sizeof(temp->destination));
        for (int i = 0; i < 10; i++)
        {
            fwrite(temp, sizeof(struct Train), 1, file);
            temp->freeSpace = GetRandomNumber(0, 10);
            temp->departureTime = new Time();
            memcpy(temp->destination, cities[GetRandomNumber(0, 4)], sizeof(temp->destination));
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
        cout << "Train -" << out->destination << " space -" << out->freeSpace << "\tTime" << out->departureTime->hour << endl;
    }


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
