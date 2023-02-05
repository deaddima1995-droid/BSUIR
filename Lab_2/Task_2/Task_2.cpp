/*
13. В кассе хранится информация о поездах на ближайшую неделю: 
- дата выезда, +
- пункт назначения, +
- время отправления, +
- число свободных мест. 
Необходимо зарезервировать m мест до города N на k-й день недели с временем отправления поезда не позднее t часов. 
Вывести время отправления или сообщение о невозможности выполнить заказ. Ключ: число свободных мест.
*/
#include <iostream>

using namespace std;

struct Time {
    Time() {}
    Time(int hour, int minute, int second) {
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }
    int hour, minute, second;
};

struct Date {
    int day, month, year;
};

struct Train {
    Time departureTime{};
    Date departureDate{};
    char destination[15];
    uint32_t freeSpace{};
};






int main() {
    cout << "Hello World!\n";
}

