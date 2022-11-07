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

struct Student {
    char firstName[10];
    int groupNumber;
};

int main() {
    struct Student first = { "Dima", 101};
    struct Student second = { "Irina", 202 };
    struct Student input;
  
    FILE* fp;

    try {
        fopen_s(&fp, "data.txt", "wb+");
    } catch (const std::exception&) {
        perror("Error open file");
    }
    fwrite(&first, sizeof(struct Student), 1, fp);
    fwrite(&second, sizeof(struct Student), 1, fp);
    
    fclose(fp);
    
    try {
        fopen_s(&fp, "data.txt", "rb");
    }
    catch (const std::exception&) {
        perror("Error open file");
    }
    
    while(fread(&input, sizeof(struct Student), 1, fp))
    printf("Name - %s, Group - %d", input.firstName, input.groupNumber);
    
    fclose(fp);
    
}



