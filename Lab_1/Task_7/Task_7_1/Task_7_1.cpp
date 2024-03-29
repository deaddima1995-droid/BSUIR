﻿/*Написать программу обработки файла записей,
содержащую следующие пункты меню: «Создание», «Просмотр», «Добавление», «Решение индивидуального задания».
Каждая запись должна содержать следующую информацию о студентах:
– фамилия; +
– номер группы; +
– оценки за семестр: по физике, математике, информатике; +1
– средний балл. +
Организовать ввод исходных данных, средний балл рассчитать по введенным оценкам. +
Содержимое всего файла и результаты решения индивидуального задания записать в текстовый файл. +
***Индивидуальное задание:
13. Вычислить общий средний балл студентов интересующей вас группы и распечатать список студентов этой группы,  -
имеющих средний балл выше общего.
*/
#include <iostream>
#include <string.h>

using namespace std;

#define MAX_LENGTH 20
#define MAX_NAME 15

FILE *file;

struct student {
    char first_name[MAX_NAME]{};
    int group_number{};
    int marks[3][MAX_LENGTH]{};
    double averageMark{};

    double getAverageMark() {
        int countMarks = 0;
        int sum = 0;
        for (auto &mark: marks) {
            for (int g: mark) {
                if (g > 0) {
                    sum += g;
                    countMarks++;
                }
            }
        }
        return (countMarks == 0) ? 0 : sum / (countMarks * 1.0);
    }

};

void consolePause();

int menu();

void addInformationToStudent(student *student);

void setFilename(char *name);

int getCountOfStudentFromFile(char *fileName);

student** getArrayFromFile(char* fileName, int students);

bool sortByAlphava(char* first, char* second);

int main() {


    system("chcp 1251");
    system("cls");
    while (true) {
        switch (menu()) {
            case 1: {                                       // Создать бинарный файл
                char *fileName = new char[MAX_LENGTH];
                setFilename(fileName);
                if (fopen_s(&file, fileName, "wb+") == NULL) {
                    int countOfStudents;
                    cout << "\nВведите колличество студентов, для добавления в файл:";
                    cin >> countOfStudents;
                    for (int x = 0; x < countOfStudents; x++) {
                        auto *temp = new student;
                        addInformationToStudent(temp);
                        fwrite(temp, sizeof(struct student), 1, file);

                    }
                    system("cls");
                    cout << "\033[31m" << "File "<< "\033[32m"  << fileName << " was created\n" << "\033[0m";
                    consolePause();
                    fclose(file);
                }
                delete[] fileName;
                break;
            }
            case 2: {                               // Вывести на экран данные из бинарного файла
                char *fileName = new char[MAX_LENGTH];
                setFilename(fileName);
                fopen_s(&file, fileName, "rb");
                if (file == nullptr) {
                    system("cls");
                    cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << fileName << "\033[0m" << endl;
                    consolePause();
                    break;
                }
                system("cls");
                cout << "\033[32mОткрыт файл: " << fileName << "\033[0m" << endl;
                auto *temp = new student;
                while (fread(temp, sizeof(struct student), 1, file)) {
                    cout << "Студент - " << temp->first_name << "\tГруппа - " << temp->group_number << "\tСредний балл - "
                         << temp->averageMark << endl;
                    cout << "\tОценки:\n";
                    for (int i = 0; i < 3; i++) {
                        if (i == 0) {
                            cout << "\t\tФизика: ";
                        } else if (i == 1) {
                            cout << "\t\tМатематика: ";
                        } else if (i == 2) {
                            cout << "\t\tИнформатика: ";
                        }
                        for (int j = 0; j < MAX_LENGTH; j++) {
                            if (temp->marks[i][j] > 0) {
                                cout << temp->marks[i][j] << " ";
                            }
                        }
                        cout << "\n";
                    }
                    cout << "\n";
                }
                delete temp;
                fclose(file);
                consolePause();
                system("cls");

                delete[] fileName;
                break;
            }
            case 3: {                               // Добавить студента в бинарный файл
                char *fileName = new char[MAX_LENGTH];
                auto *tmpStudent = new student;
                setFilename(fileName);
                if (getCountOfStudentFromFile(fileName) == -1) break;

                fopen_s(&file, fileName, "ab");
                if (file == nullptr) {
                    system("cls");
                    cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << fileName << "\033[0m"
                         << endl;
                    consolePause();
                    break;
                }
                addInformationToStudent(tmpStudent);
                system("cls");

                fwrite(tmpStudent, sizeof(struct student), 1, file);
                cout << "Студент: " << tmpStudent->first_name << " был добавлен в файл - " << fileName << endl;

                consolePause();
                fclose(file);

                delete tmpStudent;
                delete[] fileName;
                break;
            }
            case 4: {                               // Выполнение индивидуального задания задания. Вывести список студентов со средним баллом выше среднего определенной группы
                system("cls");
                char fileName[MAX_LENGTH];
                int countOfStudent{};
                setFilename(fileName);
                countOfStudent = getCountOfStudentFromFile(fileName);
                if (countOfStudent == -1) break;
                auto allStudent = getArrayFromFile(fileName, countOfStudent);
                

                double averageMarkFromGroup = 0;
                int currentGroup;
                int countStudentFromGroup = 0;
                cout << "Введите номер группы:";
                cin >> currentGroup;
                for (int i = 0; i < countOfStudent; i++) {
                    if (currentGroup == allStudent[i]->group_number) {
                        averageMarkFromGroup += allStudent[i]->averageMark;
                        countStudentFromGroup++;
                    }
                }
                if(countStudentFromGroup == 0) {
                    cout << "\033[31m" << "Нет студентов такой группы\n" << "\033[0m";
                    consolePause();
                    break;
                }
                averageMarkFromGroup /= (double) countStudentFromGroup;
                strncat_s(fileName, "_out.txt", 8);
                fopen_s(&file, fileName, "ab");
                fprintf_s(file, "Средняя оценка по группе  №%d - %.2lf баллов\n", currentGroup, averageMarkFromGroup);
                printf("Средняя оценка по группе  №%d - %.2lf баллов\n", currentGroup, averageMarkFromGroup);
                cout << "Студенты имеющие средний балл выше общего:\n";
                fprintf_s(file, "Студенты имеющие средний балл выше общего:\n");
                for (int i = 0; i < countOfStudent; i++) {
                    if (currentGroup == allStudent[i]->group_number && averageMarkFromGroup < allStudent[i]->averageMark) {
                        cout << allStudent[i]->first_name << "\tсредний балл: " << allStudent[i]->averageMark << endl;
                        fprintf_s(file, "%s - средний балл - %.2lf\n", allStudent[i]->first_name, allStudent[i]->averageMark);
                    }
                }
                consolePause();
                system("cls");
                fclose(file);
                break;
            }
            case 5: {                               // Запись в текстовый файл данные из бинарного файла
                system("cls");
                char fileName[MAX_LENGTH + 4];
                int countStudent = 0;

                setFilename(fileName);
                countStudent = getCountOfStudentFromFile(fileName);
                if (countStudent == -1) break;

                auto allStudent = getArrayFromFile(fileName, countStudent);
                
                strcat_s(fileName, "_out.txt");
                fopen_s(&file, fileName, "wt");
                fprintf_s(file, "Список студентов:\n");
                for (int i = 0; i < countStudent; i++) {
                    fprintf_s(file, "\tИмя - %s\t Группа - %d\t Средний балл - %.2lf\n", allStudent[i]->first_name,
                              allStudent[i]->group_number, allStudent[i]->averageMark);
                    for (int g = 0; g < 3; g++) {
                        if (g == 0) {
                            fprintf_s(file, "\t\tФизика: ");
                        } else if (g == 1) {
                            fprintf_s(file, "\t\tМатематика: ");
                        } else {
                            fprintf_s(file, "\t\tИнформатика: ");
                        }
                        for (int k = 0; k < MAX_LENGTH; k++) {
                            if (allStudent[i]->marks[g][k] > 0) {
                                fprintf_s(file, "%d ", allStudent[i]->marks[g][k]);
                            }
                        }
                        fprintf_s(file, "\n");
                    }
                    fprintf_s(file, "\n");
                }
                fclose(file);
                cout << "\033[31m" << "Данные записаны в файл: " << "\033[32m" << fileName << "\033[0m" << endl;
                consolePause();
                break;
            }
            case 6: {                                                             // Редактирование записи студента
                char fileName[MAX_LENGTH];
                setFilename(fileName);
                int countOfStudent = getCountOfStudentFromFile(fileName);
                if (countOfStudent < 1) {
                    cout << "В файле нет данных студентов\n";
                    break;
                }
                char* name = new char[MAX_NAME];
                int numberGroup{};
                auto tempStudent = getArrayFromFile(fileName, countOfStudent);
                cout << "Введите имя студента:";
                cin >> name;
                cout << "Введите номер группы:";
                cin >> numberGroup;
                bool isMade{};

                fopen_s(&file, fileName, "wb+");
                for (int i = 0; i < countOfStudent; i++) {
                    if (strcmp(tempStudent[i]->first_name, name) == 0 && tempStudent[i]->group_number == numberGroup && !isMade) {
                        auto temp = new student;
                        addInformationToStudent(temp);
                        fwrite(temp, sizeof(struct student), 1, file);
                        cout << "Студент - " << name << " № " << numberGroup << " изменен " << fileName << endl;
                        delete temp;
                        isMade = true;
                    }
                    else {
                        fwrite(tempStudent[i], sizeof(struct student), 1, file);
                    }
                }
                if (!isMade) cout << "Студент - " << name << " № " << numberGroup << " отсутствует в файле " << fileName << endl;
                fclose(file);

                break;
            }
            case 7: {                                                             // Удаление записи студента
                char fileName[MAX_LENGTH];
                setFilename(fileName);
                int countOfStudent = getCountOfStudentFromFile(fileName);
                if (countOfStudent < 1) {
                    cout << "В файле нет данных студентов\n";
                    break;
                }
                auto tempStudent = getArrayFromFile(fileName, countOfStudent);
                char* name = new char[MAX_NAME];
                int numberGroup{};
                bool isMade{};
                cout << "Введите имя студента:";
                cin >> name;
                cout << "Введите номер группы:";
                cin >> numberGroup;

                
                fopen_s(&file, fileName, "wb+");
                for (int i = 0; i < countOfStudent; i++) {
                    if (strcmp(tempStudent[i]->first_name, name) == 0 && tempStudent[i]->group_number == numberGroup) {
                        isMade = true;
                        cout << "Студент - " << name << " № " << numberGroup << " удален из файла " << fileName << endl;
                    } else {
                        fwrite(tempStudent[i], sizeof(struct student), 1, file);
                    }
                }

                fclose(file);

                if (!isMade) {
                    cout << "Студент - " << name << " № " << numberGroup << " отсутствует в файле " << fileName << endl;
                }
                consolePause();
                system("cls");
                break;
                
            }
            case 8: {                                                             // Сортировка по номеру группы
                char fileName[MAX_LENGTH];
                setFilename(fileName);
                int countOfStudent = getCountOfStudentFromFile(fileName);
                if (countOfStudent < 1) {
                    cout << "В файле нет данных студентов\n";
                    break;
                }
                auto tempStudent = getArrayFromFile(fileName, countOfStudent);

                int z = 1;
                while (z < countOfStudent) {
                    if (tempStudent[z - 1]->group_number <= tempStudent[z]->group_number) {
                        z += 1;
                    } else {
                        auto temp = new student;
                        temp = tempStudent[z];
                        tempStudent[z] = tempStudent[z - 1];
                        tempStudent[z - 1] = temp;
                        if (z > 1) {
                            z -= 1;
                        }
                    }

                }
                fopen_s(&file, fileName, "wb+");
                for (int i = 0; i < countOfStudent; i++) {
                    fwrite(tempStudent[i], sizeof(struct student), 1, file);
                }
                fclose(file);
                
                break;
            }
            case 9: {                                               // Сортировка по алфавиту
                char fileName[MAX_LENGTH];
                setFilename(fileName);
                int countOfStudent = getCountOfStudentFromFile(fileName);
                if (countOfStudent < 1) {
                    cout << "В файле нет данных студентов\n";
                    break;
                }
                auto tempStudent = getArrayFromFile(fileName, countOfStudent);

                int z = 1;
                while (z < countOfStudent) {
                    if (!sortByAlphava(tempStudent[z]->first_name, tempStudent[z - 1]->first_name)) {
                        z += 1;
                    }
                    else {
                        auto temp = new student;
                        temp = tempStudent[z - 1];
                        tempStudent[z - 1] = tempStudent[z];
                        tempStudent[z] = temp;
                        if (z > 1) {
                            z -= 1;
                        }
                    }

                }
                fopen_s(&file, fileName, "wb+");
                for (int i = 0; i < countOfStudent; i++) {
                    fwrite(tempStudent[i], sizeof(struct student), 1, file);
                }
                fclose(file);
                cout << "Файл отсортирован";
                break;
            }
            case 0:
                return 0;
                // Выход из программы
            default:
                puts("Ошибка, введите номер пункта ->\n");
        }
    }
}

int menu() {
    cout << "\033[32m-----Меню-----\033[0m\n";
    cout << "1. Создать файл\n";
    cout << "2. Просмотр файла\n";
    cout << "3. Добавить студента в файл\n";
    cout << "4. Список студентов группы со средним баллом выше общего\n";
    cout << "5. Сохранить из бинарного файла в текстовый файл\n";
    cout << "6. Редактировать данные студента\n";
    cout << "7. Удалить запись по имени и группе\n";
    cout << "8. Сортировать данные по группам\n";
    cout << "9. Сортировать данные по алфавиту\n";
    cout << "0. Закрыть программу\n";
    int out;
    cin >> out;
    system("cls");
    return out;
}

void addInformationToStudent(student *student) {
    cout << "Введите имя студента:";
    cin >> student->first_name;
    cout << "Введите номер группы:";
    cin >> student->group_number;
    for (size_t counter = 0; counter < 3; counter++) {
        int countOfMarks;
        do {
            switch (counter) {
                case 0:
                    cout << "Колличество оценок по физике:";
                    break;
                case 1:
                    cout << "Колличество оценок по математике:";
                    break;
                case 2:
                    cout << "Колличество оценок по информатике:";
                    break;
                default:
                    cout << "Ошибка";
                    return;
            }
            cin >> countOfMarks;
        } while(countOfMarks < 0 || countOfMarks > MAX_LENGTH);

        if (countOfMarks > 0) {
            cout << "Введите оценки:";
        }
        for (int i = 0; i < countOfMarks; i++) {
            do {
                cin >> student->marks[counter][i];
            } while (student->marks[counter][i] > 10);
        }
    }
    student->averageMark = student->getAverageMark();
}

void setFilename(char *name) {
    cout << "Введите имя файла:";
    cin >> name;
}

void consolePause() {
    system("pause");
    cin.get();
}

int getCountOfStudentFromFile(char *fileName) {
    auto *tempStudent = new student;
    int countOfStudent = 0;
    fopen_s(&file, fileName, "rb");
    if (file == nullptr) {
        cout << "\033[31m" << "Ошибка открытия файла\n" << "\033[0m";
        return -1;
    }
    while (fread(tempStudent, sizeof(struct student), 1, file)) {
        countOfStudent++;
    }
    fclose(file);
    cout << "Этот файл содержит данные  " << countOfStudent << " студентов\n";
    return countOfStudent;
}

student** getArrayFromFile(char* fileName,int students) {
    auto tempStudent = new student*[students];
    for (int i = 0; i < students; i++) {
        tempStudent[i] = new student;
    }
    fopen_s(&file, fileName, "rb");
    for (int i = 0; i < students; i++){
        fread(tempStudent[i], sizeof(struct student), 1, file);
    }
    fclose(file);
    return tempStudent;
}

bool sortByAlphava(char* first, char* second) {
    for (int i = 0; i < MAX_NAME; i++) {
        if ((int)first[i] >= 65 && (int)first[i] <= 90) first[i] += 32;
        if ((int)second[i] >= 65 && (int)second[i] <= 90) second[i] += 32;
        if (first[i] < second[i]) {
            cout << first[i] << "\t" << second[i] << "\n";
             return true;
        }
        else {
            return false;
        }
    }
    
}
