﻿ /*Написать программу обработки файла записей, 
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

struct Student {
    char firstName[15];
    int groupNumber;
    int mathematics[20], physics[20], informatics[20];
    float avarage;
};

int main() {
    FILE* fp;

    try {
        fopen_s(&fp, "data.txt", "w");
    } catch (const std::exception&) {
        perror("Error open file");
    }

    
    fclose(fp);
    
    try {
        fopen_s(&fp, "data.txt", "r");
    }
    catch (const std::exception&) {
        perror("Error open file");
    }
    
    while(fread(&input, sizeof(struct Student), 1, fp))
    printf("Name - %s, Group - %d\n", input.firstName, input.groupNumber);
    
    fclose(fp);
    
}

int writeStructInFile(FILE* file) {
    if (fwrite(new Student({ "Vasya",101 }), sizeof(struct Student), 1, file) != sizeof(struct Student)) {
        return -1;
    }
    return 1;
}

void readStructFromFile(FILE* file,struct Students *students) {
    struct Student out;
    int counter = 0;
    while (fread(&out, sizeof(struct Student), 1, file)) {
        counter++;
    }
    &students = new Student[counter];
    for (int i = 0; i < counter; i++) {
        fread(&out, sizeof(struct Student), 1, file);
        students[i] = out;
    }
}



