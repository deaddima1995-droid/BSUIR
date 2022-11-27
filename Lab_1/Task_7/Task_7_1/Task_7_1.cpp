 /*Написать программу обработки файла записей, 
содержащую следующие пункты меню: «Создание», «Просмотр», «Добавление», «Решение индивидуального задания».
Каждая запись должна содержать следующую информацию о студентах:
– фамилия;
– номер группы;
– оценки за семестр: по физике, математике, информатике;
– средний балл.
Организовать ввод исходных данных, средний балл рассчитать по введенным оценкам.
Содержимое всего файла и результаты решения индивидуального задания записать в текстовый файл.

13. Вычислить общий средний балл студентов интересующей вас группы и распечатать список студентов этой группы, 
имеющих средний балл выше общего.
*/
#include <iostream>

using namespace std;

FILE* file;

void readStructFromFile(FILE* file);
int writeStructInFile(FILE* file);
int Menu();
void CreateFile();
void OpenFile();

struct Student {
    char firstName[15];
    int groupNumber;
};

int main() {

    while (true) {
        switch (Menu()) {
        case 1: CreateFile();   break;
        case 2: OpenFile();     break;
        case 0: return 0;
        default: puts("Write correct number!\n");
        }
    }
    /*
    fopen_s(&file, "student.txt", "wb+");
    writeStructInFile(file);
    fclose(file);
    fopen_s(&file, "student.txt", "rb");
    readStructFromFile(file);
    */
}

int writeStructInFile(FILE* file) {
    int i;
    cin >> i;
    for (int x = 0; x < i; x++){ 
        char name[15];
        int group;
        cin >> name;
        cin >> group;
        Student temp;
        strcpy_s(temp.firstName, name);
        temp.groupNumber = group;
        fwrite(&temp, sizeof(struct Student), 1, file);
    }
    return 1;
}

int Menu() {
    cout << "Menu:\n";
    cout << "1. Create File\n";
    cout << "2. Open File\n";
    cout << "0. Close program\n";
    int out;
    cin >> out;
    return out;
}

void CreateFile() {
    char name[20];

    cout << "Write file name:";
    cin >> name;
    try {
        fopen_s(&file, name, "wb+");
        fclose(file);
        cout << "File " << name << " was created\n";
    } catch (const std::exception&) {
        cout << "Error with creating file\n";
    }
}

void OpenFile() {
    char name[20];

    cout << "Write file name:";
    cin >> name;

    if (fopen_s(&file, name, "r+") == NULL) {
        fclose(file);
        cout << "File " << name << " was opened\n";
    } else {
        cout << "Error with opening " << name << "\n";
    }
    
}

void readStructFromFile(FILE* file) {
    Student out;
    int counter = 0;
    while (fread(&out, sizeof(struct Student), 1, file)) {
        printf("Student's name - %s, group - %d\n", out.firstName, out.groupNumber);
    }
}



