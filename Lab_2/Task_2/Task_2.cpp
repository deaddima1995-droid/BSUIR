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

    int hour, minute;
};

struct Train {
    Train() {
        this->departureTime = Time();
        this->freeSpace = 0;
    }

    Train(int hour, int date, int destiny, int freeSpace) {
        this->departureTime.hour = hour;
        this->departureTime.minute = 0;
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
    out << ":" << 0 << time.minute;
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

void addTrainToFile(char *fileName, Train *train);

void selectionSort(Train **trains, int counter);

void quickSort(Train **trains, int low, int high);

int getRandomNumber(int min, int max);

int menu();

Train *getRandomTrain();

Train *getTrain();

Train **getTrainsFromFile(char *fileName, int *counter);


int main() {
    system("chcp 1251");
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
                addTrainToFile(name, getTrain());
                system("pause");
                cin.get();
                break;
            }
            case 4: {
                cout << "Введите данные на какой поезд вы хотите сделать заказ:\n";
                Train *train = getTrain();
                int *countTrains = new int;
                bool isHaveKey = false;
                *countTrains = 0;
                Train **trains = getTrainsFromFile(name, countTrains);


                fstream file(name, std::fstream::in | std::fstream::binary);
                if (!file.is_open()) {
                    cerr << "Нельзя открыть файл для чтения\n";
                    break;
                }


                if (*countTrains < 1 || trains == nullptr) {
                    cout << "Поездов в файле нет.\n";
                } else {
                    cout << "Список поездов:\n";
                    for (int i = 0; i < *countTrains; ++i) {
                        cout << trains[i] << endl;
                    }
                }
                for (int i = 0; i < *countTrains; ++i) {
                    if (train->freeSpace <= trains[i]->freeSpace &&
                        train->departureTime.hour <= trains[i]->departureTime.hour &&
                        strcmp(train->destination, trains[i]->destination) == 0 &&
                        strcmp(train->departureDate, trains[i]->departureDate) == 0) {
                        isHaveKey = true;
                        trains[i]->freeSpace -= train->freeSpace;
                        cout << "Заказ сделан.\n";
                        break;
                    }
                }
                if (isHaveKey) {
                    file.clear();
                    file.close();
                    for (int i = 0; i < *countTrains; ++i) {
                        addTrainToFile(name, trains[i]);
                    }
                } else {
                    cout << "Поезда с таким описанием нет в базе, либо не хватает свободных мест\n";
                    file.close();
                }

                system("pause");
                cin.get();
                break;
            }
            case 5: {
                cout << "Введите данные на какой поезд вы хотите сделать заказ:\n";
                Train *train = getTrain();
                int *countTrains = new int;
                bool isHaveKey = false;
                *countTrains = 0;
                Train **trains = getTrainsFromFile(name, countTrains);

                fstream file(name, std::fstream::in | std::fstream::binary);
                if (!file.is_open()) {
                    cerr << "Нельзя открыть файл для чтения\n";
                    break;
                }
                if (*countTrains < 1 || trains == nullptr) {
                    cout << "Поездов в файле нет.\n";
                } else {
                    cout << "Список поездов:\n";
                    for (int i = 0; i < *countTrains; ++i) {
                        cout << trains[i] << endl;
                    }
                }
                file.close();
                int left = 0, right = *countTrains - 1;
                while (left <= right) {
                    int mid = left + (right - left) / 2;
                    if (train->freeSpace == trains[mid]->freeSpace &&
                        train->departureTime.hour <= trains[mid]->departureTime.hour &&
                        strcmp(train->destination, trains[mid]->destination) == 0 &&
                        strcmp(train->departureDate, trains[mid]->departureDate) == 0) {
                            isHaveKey = true;
                            trains[mid]->freeSpace -= train->freeSpace;
                            break;
                    } else if (trains[mid]->freeSpace < train->freeSpace) {
                            left = mid + 1;
                    } else {
                            right = mid - 1;
                    }
            }
                if (left == right) {
                    cout << "Поездов нет, заказа сделать нельзя";
                    file.close();
                } else {
                    file.clear();
                    file.close();
                    cout << "Заказ будет сделан";
                    for (int i = 0; i < *countTrains; ++i) {
                        addTrainToFile(name, trains[i]);
                    }
                }

        }
        case 6: {
            int *counter = new int;
            Train **trains = getTrainsFromFile(name, counter);
            selectionSort(trains, *counter);
            fstream file(name, std::fstream::out | std::fstream::binary);
            file.clear();
            file.seekg(0);
            file.close();
            if (trains == nullptr) break;
            for (int i = 0; i < *counter; ++i) {
                if (trains[i] != nullptr) {
                    addTrainToFile(name, trains[i]);
                }
            }
            cout << "Сортировка выполнена\n";
            system("pause");
            cin.get();
            break;
        }
        case 7: {
            int *counter = new int;
            Train **trains = getTrainsFromFile(name, counter);
            quickSort(trains, 0, *counter - 1);
            fstream file(name, std::fstream::out | std::fstream::binary);
            file.clear();
            file.seekg(0);
            file.close();
            if (trains == nullptr) break;
            for (int i = 0; i < *counter; ++i) {
                if (trains[i] != nullptr) {
                    addTrainToFile(name, trains[i]);
                }
            }
            cout << "Сортировка выполнена\n";
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
    if (!outTrain.is_open()) {
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
    if (!inTrain.is_open()) {
        cerr << "Нельзя открыть файл для чтения\n";
        return;
    }
    while (inTrain.read((char *) &rTrain, sizeof(struct Train))) {
        cout << &rTrain;
        cout << endl;
    }
    inTrain.close();
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

Train *getTrain() {
    auto *out = new Train();
    int day{};
    char *destiny = new char;
    cout << "\nВведите пункт назначения: ";
    cin >> destiny;
    strcpy_s(out->destination, destiny);
    do {
        cout << "\nВведите день недели отправления: ";
        cin >> day;
        day--;
        strcpy_s(out->departureDate, daysOfWeek[day]);
    } while (day < 1 || day > 7);

    do {
        cout << "\nВведите время отправления: ";
        cout << "\nЧас - ";
        cin >> out->departureTime.hour;
        out->departureTime.minute = 0;

    } while (out->departureTime.hour < 0 || out->departureTime.hour > 23);

    do {
        cout << "\nВведите количество свободных мест: ";
        cin >> out->freeSpace;
    } while (out->freeSpace < 1);

    return out;
}

Train *getRandomTrain() {
    return new Train(getRandomNumber(0, 23),
                     getRandomNumber(0, COUNT_DAYS - 1),
                     getRandomNumber(0, COUNT_CITIES - 1),
                     getRandomNumber(0, COUNT_FREE_SPACE));
}

Train **getTrainsFromFile(char *fileName, int *counter) {

    fstream inTrain(fileName, std::fstream::in | std::fstream::binary);
    if (!inTrain.is_open()) {
        cerr << "Нельзя открыть файл для чтения\n";
        return nullptr;
    }
    inTrain.clear();
    inTrain.seekg(0, ios::end);
    *counter = inTrain.tellg() / sizeof(Train);
    inTrain.seekg(0);
    auto **outTrains = new Train *[*counter];
    for (int i = 0; i < *counter; i++) {
        outTrains[i] = new Train;
        inTrain.read((char *) outTrains[i], sizeof(struct Train));
    }
    inTrain.close();
    return outTrains;
}

void addTrainToFile(char *fileName, Train *train) {
    fstream addTrain(fileName, std::fstream::app | std::fstream::out | std::fstream::binary);
    if (!addTrain.is_open()) {
        cout << "Нельзя открыть файл для чтения\n";
        return;
    }
    addTrain.write((char *) train, sizeof(struct Train));
    addTrain.close();
    cout << "Добавлен поезд:\n" << train << endl << endl;
}

void selectionSort(Train **trains, int counter) {
    for (int i = 0; i < counter - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < counter; ++j) {
            if (trains[j]->freeSpace > trains[min]->freeSpace) {
                min = j;
            }
        }
        Train *temp = trains[i];
        trains[i] = trains[min];
        trains[min] = temp;
    }
}

void quickSort(Train **trains, int left, int right) {
    int i = left;
    int j = right;
    Train *tmp;
    int pivot = trains[(left + right) / 2]->freeSpace;

    while (i <= j) {
        while (trains[i]->freeSpace < pivot)
            i++;
        while (trains[j]->freeSpace > pivot)
            j--;
        if (i <= j) {
            tmp = trains[i];
            trains[i] = trains[j];
            trains[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(trains, left, j);
    if (i < right)
        quickSort(trains, i, right);
}

