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

Train** getTrains();
void createFile();
void readFile();
void addTrainToFile();

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    
    struct  Train *train = new Train(true);

    
    ofstream outTrain("test", ios::out | ios::binary);
    if (!outTrain) {
        cout << "Нельзя открыть файл для записи\n";
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        train = new Train(true);
        outTrain.write((char*)train, sizeof(struct Train));
    }
    
    outTrain.close();

    ifstream inTrain("test", ios::in | ios::binary);
    if (!inTrain) {
        cout << "Нельзя открыть файл для чтения\n";
    }
    Train* rTrain = new Train();
    while (inTrain.read((char*)rTrain, sizeof(struct Train))) {
        cout << rTrain->destination << endl << rTrain->departureDate << endl << rTrain->departureTime.hour << ":" << rTrain->departureTime.minute << endl;
        cout << endl;
    }
    
    inTrain.close();

   

    
}

Train** getTrains()
{
    return nullptr;
}

void createFile(){ 
    
}

void readFile() {
    
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