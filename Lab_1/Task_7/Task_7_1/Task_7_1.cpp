/*Написать программу обработки файла записей,
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

using namespace std;

#define MAX_LENGTH 20
#define MAX_NAME 15

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

int getCountOfStudentFromFile(FILE *file, char *fileName);


int main() {
    FILE *file;

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
                    cout << "File " << fileName << " was created\n";
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
                    cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << fileName << "\033[0m"
                         << endl;
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

                fopen_s(&file, fileName, "ab");
                if (file == nullptr) {
                    system("cls");
                    cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << fileName << "\033[0m"
                         << endl;
                    system("pause");
                    cin.get();
                    break;
                }
                addInformationToStudent(tmpStudent);
                system("cls");

                if (fwrite(tmpStudent, sizeof(struct student), 1, file) == sizeof(struct student)) {
                    cout << "Студент: " << tmpStudent->first_name << " был добавлен в файл - " << fileName << endl;
                } else {
                    cout << "Ошибка, ввода данных";
                }
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
                countOfStudent = getCountOfStudentFromFile(file, fileName);

                auto allStudent = new student *[countOfStudent];
                for (int i = 0; i < countOfStudent; i++) {
                    allStudent[i] = new student;
                }
                fopen_s(&file, fileName, "rb");
                for (int i = 0; i < countOfStudent; i++) {
                    fread(allStudent[i], sizeof(struct student), 1, file);
                }
                fclose(file);

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
                averageMarkFromGroup /= (double) countStudentFromGroup;
                cout << "Средняя оценка по группе  №" << currentGroup << " - " << averageMarkFromGroup << "баллов" << endl;
                cout << "Студенты имеющие средний балл выше общего:\n";
                for (int i = 0; i < countOfStudent; i++) {
                    if (currentGroup == allStudent[i]->group_number && averageMarkFromGroup < allStudent[i]->averageMark) {
                        cout << allStudent[i]->first_name << "\tсредний балл: " << allStudent[i]->averageMark << endl;
                    }
                }
                break;
            }
            case 5: {                               // Запись в текстовый файл данные из бинарного файла
                system("cls");
                char fileName[MAX_LENGTH + 4];
                int countStudent{};

                setFilename(fileName);
                strcat_s(fileName, ".txt");
                countStudent = getCountOfStudentFromFile(file,fileName);
                auto allStudent = new student *[countStudent];
                for (int i = 0; i < countStudent; i++) {
                    allStudent[i] = new student;
                }
                fopen_s(&file, fileName, "rb");
                if (file == nullptr) {
                    cout << "Ошибка открытия " << fileName << endl;
                    break;
                }
                for (int i = 0; i < countStudent; i++) {
                    fread(allStudent[i], sizeof(struct student), 1, file);
                }
                fclose(file);
                string tmp = fileName;
                strncpy_s(fileName, fileName, strlen(fileName) - 4);
                strcat_s(fileName, "_out.txt");
                fopen_s(&file, fileName, "wt");
                fprintf_s(file, "Список студентов:\n");
                for (int i = 0; i < countStudent; i++) {
                    fprintf_s(file, "\tИмя - %s\t Группа - %d\t Средний балл - %.2lf\n", allStudent[i]->first_name,
                              allStudent[i]->group_number, allStudent[i]->averageMark);
                    for (int g = 0; g < 3; g++) {
                        if (g == 0) {
                            fprintf_s(file, "\t\tфизика: ");
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
    cout << "2. Вывести на экран данные\n";
    cout << "3. Добавить студента в файл\n";
    cout << "4. Вывести список студентов,определённой группы, со средним баллом выше общего\n";
    cout << "5. Сохранить из бинарного файла в текстовый файл\n";
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
        if (countOfMarks > 0) {
            cout << "Введите оценки:";
        }
        for (int i = 0; i < countOfMarks; i++) {
            cin >> student->marks[counter][i];
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

int getCountOfStudentFromFile(FILE *file, char *fileName) {
    auto *tempStudent = new student;
    int countOfStudent = 0;
    fopen_s(&file, fileName, "rb");
    if (file == nullptr) {
        cout << "Ошибка: в данном файле нет студентов или файл отсутствует";
        return 0;
    }
    while (fread(tempStudent, sizeof(struct student), 1, file)) {
        countOfStudent++;
    }
    fclose(file);
    cout << "Этот файл содержит данные  " << countOfStudent << " студентов\n";
    return countOfStudent;
}