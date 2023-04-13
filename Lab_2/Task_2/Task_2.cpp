/*
* 2.2. Индивидуальные задания.
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

        Ключ в поиске - время до поезда,
        а сортировать можно по количеству свободных мест
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>

#define LENGTH_CHAR_ARRAY 23
#define COUNT_DAYS 7
#define COUNT_CITIES 5
#define COUNT_FREE_SPACE 20

using namespace std;

const char daysOfWeek[COUNT_DAYS][LENGTH_CHAR_ARRAY] = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница",
                                                        "Суббота", "Воскресенье"};
const char cities[COUNT_CITIES][LENGTH_CHAR_ARRAY] = {"Минск", "Могилёв", "Брест", "Витебск", "Гродно"};
char *name = new char;


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
    char departureDate[LENGTH_CHAR_ARRAY]{};
    char destination[LENGTH_CHAR_ARRAY]{};
    int freeSpace{};
};

ostream &operator<<(ostream &out, Time &time) {
    if (time.hour < 10) {
        out << 0 << time.hour;
    } else {
        out << time.hour;
    }
    if (time.minute < 10) {
        out << ":" << 0 << time.minute;
    } else {
        out << ":" << time.minute;
    }
    return out;
}

ostream &operator<<(ostream &out, Train *train) {
    out << "Поезд направляется: " << train->destination << endl
        << "День отправления: " << train->departureDate << endl
        << "Время отправления: " << train->departureTime << endl
        << "Количество свободных мест: " << train->freeSpace << endl;
    return out;
}

void createFile(char *fileName);

void readFile(char *fileName);

void addTrainToFile(char *fileName);

void addTrainTo(char *fileName, Train *train);

int linearSearch(Train **trains, int n, int key);

int getRandomNumber(int min, int max);

int menu();

Train *getRandomTrain();

Train **getTrains(char *fileName, int *counter);


int main() {
    system("chcp 65001");
    srand(time(nullptr));

    while (true) {
        system("cls");
        cout << "Введите имя файла:";
        cin >> name;

        switch (menu()) {

            case 1: {
                createFile(name);
                system("pause");
                cin.get();
                break;
            }
            case 2: {
                readFile(name);
                system("pause");
                cin.get();
                break;
            }
            case 3: {
                addTrainToFile(name);
                system("pause");
                cin.get();
                break;
            }
            case 4: {
                int *counter = new int;
                int hour, seats, day;
                char destination[LENGTH_CHAR_ARRAY], dayArr[LENGTH_CHAR_ARRAY];

                Train **trains = getTrains(name, counter);
                if (trains == nullptr) {
                    cout << "В файле отсутствуют поезда\n";
                    system("pause");
                    cin.get();
                    break;
                }

                cout << "Список поездов в файле:\n";
                for (int i = 0; i < *counter; i++) {
                    cout << trains[i];
                }

                cout << "\nВведите пункт назначения:";
                cin >> destination;

                do {
                    cout << "\nВведите час отправления:";
                    cin >> hour;
                } while (hour < 0 || hour > 23);

                do {
                    cout << "\nВведите номер дня недели:";
                    cin >> day;
                } while (day < 1 || day > 7);
                --day;
                strcpy_s(dayArr, daysOfWeek[day]);

                do {
                    cout << "\nВведите количество необходимых мест";
                    cin >> seats;
                } while (seats < 0);

                createFile(name);
                for (int i = 0; i < *counter; ++i) {
                    if (seats <= trains[i]->freeSpace &&
                        hour <= trains[i]->departureTime.hour &&
                        strcmp(destination, trains[i]->destination) == 0 &&
                        strcmp(dayArr, daysOfWeek[day]) == 0) {

                        trains[i]->freeSpace -= seats;
                        cout << "Заказ делан.\n";
                        addTrainTo(name, trains[i]);
                        break;
                    }
                }
                system("pause");
                cin.get();
                break;
            }
            case 0: {
                return 0;
            }
            default:
                cout << "Введите пункт меню:";
                break;
        }
    }
}

int menu() {
    cout << "Текущий файл: " << name << endl;
    cout << "\033[32m-----Меню-----\033[0m\n";
    cout << "1. Создать файл\n";
    cout << "2. Просмотр файла\n";
    cout << "3. Добавить данные поезда в файл\n";
    cout << "4. Заказать билет Линейным поиском в файле\n";
    cout << "5. Заказать билет Двоичным поиск в файле\n";
    cout << "6. Сортировка методом прямого выбора\n";
    cout << "7. Сортировка Quick Sort\n";
    cout << "0. Закрыть программу\n";
    int out;
    cin >> out;
    system("cls");
    return out;
}

void createFile(char *fileName) {
    auto *train = new Train();
    int counter = 0;

    fstream outTrain(fileName, std::fstream::out | std::fstream::binary);
    if (!outTrain) {
        cerr << "Файл не создан\n";
        return;
    } else {
        cout << "Файл " << fileName << " создан\n";
    }
    cout << "Введите количество добавляемых поездов:";
    cin >> counter;

    for (int i = 0; i < counter; i++) {
        train = getRandomTrain();
        outTrain.write((char *) train, sizeof(struct Train));
    }
    outTrain.close();
}

void readFile(char *fileName) {
    Train rTrain;

    fstream inTrain(fileName, std::fstream::in | std::fstream::binary);
    if (!inTrain) {
        cerr << "Нельзя открыть файл для чтения\n";
        return;
    }
    while (inTrain.read((char *) &rTrain, sizeof(struct Train))) {
        cout << &rTrain;
        cout << endl;
    }
    inTrain.close();
}

void addTrainToFile(char *fileName) {
    Train train;

    fstream addTrain(fileName, std::fstream::app | std::fstream::out | std::fstream::binary);
    if (!addTrain) {
        cout << "Нельзя открыть файл для чтения\n";
        return;
    }
    cout << "Введите пункт назначения: ";
    cin >> train.destination;
    cout << "Введите день отправления:";
    cin >> train.departureDate;
    cout << "Введите время отправления";
    cin >> train.departureTime.hour;
    cin >> train.departureTime.minute;
    cout << "Введите количество свободных мест";
    cin >> train.freeSpace;

    addTrain.write((char *) &train, sizeof(struct Train));
    addTrain.close();
    cout << "Добавлен поезд" << &train << endl << endl;
}

int linearSearch(Train **trains, int n, int key) {
    for (int i = 0; i < n; i++) {
        if (trains[i]->freeSpace <= key) {
            return i;
        }
    }
    return -1;
}

int binarySearch(string filename, int key) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file\n";
        return -1;
    }
    int left = 0, right = -1;
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    if (size > 0) {
        right = (size / sizeof(int)) - 1;
    }
    while (left <= right) {
        int mid = left + (right - left) / 2;
        file.seekg(mid * sizeof(int), ios::beg);
        int value;
        file.read((char *) &value, sizeof(value));
        if (value == key) {
            file.close();
            return mid;
        } else if (value < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    file.close();
    return -1;
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

Train *getRandomTrain() {
    return new Train(getRandomNumber(0, 23),
                     getRandomNumber(0, 59),
                     getRandomNumber(0, COUNT_DAYS - 1),
                     getRandomNumber(0, COUNT_CITIES - 1),
                     getRandomNumber(0, COUNT_FREE_SPACE));
}

Train **getTrains(char *fileName, int *counter) {
    int count = 0;

    auto *rTrain = new Train();
    fstream inTrain(fileName, std::fstream::in | std::fstream::binary);
    if (!inTrain) {
        cerr << "Нельзя открыть файл для чтения\n";
        return nullptr;
    }
    while (inTrain.read((char *) rTrain, sizeof(struct Train))) {
        count++;
    }
    delete rTrain;
    inTrain.clear();
    inTrain.seekg(0);
    *counter = count;
    auto **outTrains = new Train *[count];
    for (int i = 0; i < count; i++) {
        outTrains[i] = new Train;
        inTrain.read((char *) outTrains[i], sizeof(struct Train));
    }
    inTrain.close();
    return outTrains;
}

void addTrainTo(char *fileName, Train *train) {
    fstream addTrain(fileName, std::fstream::app | std::fstream::out | std::fstream::binary);
    if (!addTrain) {
        cout << "Нельзя открыть файл для чтения\n";
        return;
    }
    addTrain.write((char *) train, sizeof(struct Train));
    addTrain.close();
    cout << "Добавлен поезд" << train << endl << endl;
    delete train;
}
