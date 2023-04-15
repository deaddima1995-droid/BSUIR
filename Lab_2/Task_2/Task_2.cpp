/*
* 2.2. �������������� �������.
�������� ��������� ��������� ����� ������, ��������� �� ��������, � ������� ����������� ��������� �������:
    ����������� ��������� ����� (��������, ��������, ����������);
    �������� ����� � �����;
    ���������� ������� (�����) �������� ������� ������ � QuickSort;
    �������� ����� � ��������������� �������.
*
        13. � ����� �������� ���������� � ������� �� ��������� ������:
        - ���� ������, +
        - ����� ����������, +
        - ����� �����������, +
        - ����� ��������� ����.
        ���������� ��������������� m ���� �� ������ N �� k-� ���� ������ � �������� ����������� ������ �� ������� t �����.
        ������� ����� ����������� ��� ��������� � ������������� ��������� �����. ����: ����� ��������� ����.

        �������� �����

        ���� � ������ - ����� �� ������,
        � ����������� ����� �� ���������� ��������� ����
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

const char daysOfWeek[COUNT_DAYS][LENGTH_CHAR_ARRAY] = {"�����������", "�������", "�����", "�������", "�������",
                                                        "�������", "�����������"};
const char cities[COUNT_CITIES][LENGTH_CHAR_ARRAY] = {"�����", "������", "�����", "�������", "������"};
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
    out << "����� ������������: " << train->destination << endl
        << "���� �����������: " << train->departureDate << endl
        << "����� �����������: " << train->departureTime << endl
        << "���������� ��������� ����: " << train->freeSpace << endl;
    return out;
}

void createFile(char *fileName);

void readFile(char *fileName);

void addTrainToFile(char *fileName, Train *train);

int linearSearch(Train **trains, int n, int key);

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
        cout << "������� ��� �����:";
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
                addTrainToFile(name,getTrain());
                system("pause");
                cin.get();
                break;
            }
            case 4: {

                fstream file(name, std::fstream::in | std::fstream::binary);
                if (!file.is_open()) {
                    cerr << "������ ������� ���� ��� ������\n";
                    break;
                }
                file.close();
                system("pause");
                cin.get();
                break;
            }
            case 0: {
                return 0;
            }
            default:
                cout << "������� ����� ����:";
                break;
        }
    }
}

int menu() {
    cout << "������� ����: " << name << endl;
    cout << "\033[32m-----����-----\033[0m\n";
    cout << "1. ������� ����\n";
    cout << "2. �������� �����\n";
    cout << "3. �������� ������ ������ � ����\n";
    cout << "4. �������� ����� �������� ������� � �����\n";
    cout << "5. �������� ����� �������� ����� � �����\n";
    cout << "6. ���������� ������� ������� ������\n";
    cout << "7. ���������� Quick Sort\n";
    cout << "0. ������� ���������\n";
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
        cerr << "���� �� ������\n";
        return;
    } else {
        cout << "���� " << fileName << " ������\n";
    }
    cout << "������� ���������� ����������� �������:";
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
        cerr << "������ ������� ���� ��� ������\n";
        return;
    }
    while (inTrain.read((char *) &rTrain, sizeof(struct Train))) {
        cout << &rTrain;
        cout << endl;
    }
    inTrain.close();
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

Train *getTrain() {
    auto *out = new Train();
    int day{};
    char *destiny = new char ;
    cout << "\n������� ����� ����������: ";
    cin >> destiny;
    strcpy_s(out->destination, destiny);
    do {
        cout << "\n������� ���� ������ �����������: ";
        cin >> day;
        day++;
        strcpy_s(out->departureDate, daysOfWeek[day]);
    } while (day < 1 || day > 7 );

    do {
        cout << "\n������� ����� �����������: ";
        cout << "\n��� - ";
        cin >> out->departureTime.hour;
        out->departureTime.minute = 0;

    } while(out->departureTime.hour < 0 || out->departureTime.hour > 23);

    do {
        cout << "\n������� ���������� ��������� ����: ";
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
        cerr << "������ ������� ���� ��� ������\n";
        return nullptr;
    }
    inTrain.clear();
    inTrain.seekg(0, ios::end);
    *counter = (int) inTrain.tellg();
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
        cout << "������ ������� ���� ��� ������\n";
        return;
    }
    addTrain.write((char *) train, sizeof(struct Train));
    addTrain.close();
    cout << "�������� �����:\n" << train << endl << endl;
}

