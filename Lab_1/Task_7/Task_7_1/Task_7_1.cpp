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

void readStructFromFile(FILE* file,struct Student &students);
int writeStructInFile(FILE* file);

struct Student {
    char firstName[15];
    int groupNumber;
};

int main() {
    Student *students = new Student;
    FILE* file;
    fopen_s(&file, "student.txt", "w");
    writeStructInFile(file);
    readStructFromFile(file, *students);
    /*
    FILE* fp;

    try {
        fopen_s(&fp, "data.txt", "r");
    } catch (const std::exception&) {
        perror("Error open file");
    }
    writeStructInFile(fp);
    fclose(fp);
    
    try {
        fopen_s(&fp, "data.txt", "r");
    }
    catch (const std::exception&) {
        perror("Error open file");
    }
    Student *now = new Student[5];
    readStructFromFile(fp, now);
    for (size_t i = 0; i < sizeof(now); i++)
    {
        printf("Name - %s, Group - %d\n", now[i].firstName, now[i].groupNumber);
    }
    fclose(fp);
    
    //writeStructInFile(fp);
    readStructFromFile(fp, now);
    for (size_t i = 0; i < sizeof(now); i++)
    {
        printf("Name - %s, Group - %d\n", now[i].firstName, now[i].groupNumber);
    }
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
        Student* temp = new Student();
        strcpy_s(temp->firstName, name);
        temp->groupNumber = group;
        fwrite(temp, sizeof(struct Student), 1, file);
    }
    return 1;
}

void readStructFromFile(FILE* file,struct Student &students) {
    struct Student out;
    int counter = 0;
    while (fread(&out, sizeof(struct Student), 1, file)) {
        printf("Student's name - %s, group - %d", out.firstName, out.groupNumber);
    }
}



