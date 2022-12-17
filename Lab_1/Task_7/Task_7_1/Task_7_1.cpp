/*Написать программу обработки файла записей,
содержащую следующие пункты меню: «Создание», «Просмотр», «Добавление», «Решение индивидуального задания».
Каждая запись должна содержать следующую информацию о студентах:
– фамилия; +
– номер группы; +
– оценки за семестр: по физике, математике, информатике; +1
– средний балл. +
Организовать ввод исходных данных, средний балл рассчитать по введенным оценкам. +
Содержимое всего файла и результаты решения индивидуального задания записать в текстовый файл. +

13. Вычислить общий средний балл студентов интересующей вас группы и распечатать список студентов этой группы,  -
имеющих средний балл выше общего.
*/
#include <iostream>

using namespace std;
#define MAX_LENGTH 20
#define MAX_NAME 15
#define MAX_PERSONAL_TASKS 10

constexpr int max_length = 20;

FILE *file;

struct student {
    char first_name[MAX_NAME]{};
    int group_number{};
    int marks[3][MAX_LENGTH]{};
    int personal_tasks[MAX_PERSONAL_TASKS]{};
    double averageMark = 0;

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
        for (int personal_task: personal_tasks) {
            if (personal_task > 0) {
                sum += personal_task;
                countMarks++;
            }
        }
        return (countMarks == 0) ? 0 : sum / (countMarks * 1.0);
    }

};

void readStructFromFile(FILE *file, char* fileName);

void consolePause();

void writeBinaryDataAsText(FILE *file);

int writeStructInFile(FILE *file);

int menu();

int subMenuOpenFile();

void addInformationToStudent(student *student);

void setFilename(char *name);

void makePersonalTask(FILE *file);

void printStudentLintByGroupFromAverageMark(FILE *file);

int getCountOfStudentFromFile(FILE *file, char *fileName);


int main() {
    system("chcp 1251");
    system("cls");
    while (true) {
        MainMenu:
        switch (menu()) {
                    // case 1 нужно проверить
            case 1: {                                       // Создать бинарный файл
                char *name = new char[max_length];
                setFilename(name);

                if (fopen_s(&file, name, "wb+") == NULL) {
                    writeStructInFile(file);
                    system("cls");
                    cout << "File " << name << " was created\n";
                    delete[] name;
                }
                fclose(file);
                break;
            }

            case 2: // Sub menu Open File
            SubMenu:
                while (true) {

                    switch (subMenuOpenFile()) {
                        case 1: {                               // Вывести на экран данные из бинарного файла
                            char *fileName = new char[max_length];
                            setFilename(fileName);
                            readStructFromFile(file, fileName);
                            delete[] fileName;
                            break;
                        }
                        case 2: {                               // Добавить студента в бинарный файл
                            char *fileName = new char[max_length];
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
                        case 3: {                               // Выполнение "персонального" задания
                            system("cls");
                            makePersonalTask(file);
                            break;
                        }
                        case 4: {                               // Запись в текстовый файл данные из бинарного файла
                            system("cls");
                            writeBinaryDataAsText(file);
                            break;
                        }
                        case 5: {                               // Вывести список студентов со средним баллом выше среднего определенной группы
                            printStudentLintByGroupFromAverageMark(file);
                            break;
                        }
                        case 0: {                               // Выход из под-меню "Open file"
                            system("cls");
                            goto MainMenu;
                            break;
                        }
                        default: {                              // Если пользователь ввел что-то не верное
                            system("cls");
                            cout << "Ошибка, введите номер пункта ->\n";
                            goto SubMenu;
                            break;
                        }
                    }
                }

            case 0:
                return 0;                               // Выход из программы
            default:
                puts("Ошибка, введите номер пункта ->\n");
        }
    }
}


int menu() {
    cout << "\033[32m-----Меню-----\033[0m\n";
    cout << "1. Создать файл\n";
    cout << "2. Открыть файл\n";
    cout << "0. Закрыть программу\n";
    int out;
    cin >> out;
    system("cls");
    return out;
}

int subMenuOpenFile() {
    cout << "\033[32m--Открыть файл:--\033[0m\n";
    cout << "1. Вывести на экран список студентов\n";
    cout << "2. Добавить студента в файл\n";
    cout << "3. Выполнить индивидуальное задание для студента\n";
    cout << "4. Сохранить в текстовый файл\n";
    cout << "5. Вывести список студентов,определённой группы, со средним баллом выше общего\n";
    cout << "0. Выйти в основное меню\n";
    int out;
    cin >> out;
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
        }
        cin >> countOfMarks;
        if (countOfMarks > 0) {
            cout << "Вводите оценки:";
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

void makePersonalTask(FILE *file) {
    int countOfStudent = 0;
    int equalStudent = -1;
    char fileName[max_length];
    setFilename(fileName);
    countOfStudent = getCountOfStudentFromFile(file, fileName);
    if (countOfStudent == 0) {
        return;
    }
    auto **allStudent = new student *[countOfStudent];
    for (int i = 0; i < countOfStudent; i++) {
        allStudent[i] = new student;
    }
    auto *tempStudent = new student;
    cout << "Имя студента:";
    cin >> tempStudent->first_name;
    cout << "Номер группы:";
    cin >> tempStudent->group_number;
    string s1;
    s1 = tempStudent->first_name;


    fopen_s(&file, fileName, "rb");
    for (int i = 0; i < countOfStudent; i++) {
        fread(allStudent[i], sizeof(struct student), 1, file);
        string s2 = allStudent[i]->first_name;
        if (s1 == s2 && allStudent[i]->group_number == tempStudent->group_number) {
            cout << "В файле есть такой студент: " << tempStudent->first_name << "\t" << tempStudent->group_number
                 << endl;
            tempStudent = allStudent[i];
            equalStudent = i;
        }
    }

    fclose(file);

    if (equalStudent != -1) {
        fopen_s(&file, fileName, "wb");
        for (int i = 0; i < countOfStudent; i++) {
            if (i != equalStudent) {
                fwrite(allStudent[i], sizeof(struct student), 1, file);
            } else {
                int mark = 0;
                cout << "Введите оценку за персональное задание:";
                cin >> mark;
                for (int & personal_task : tempStudent->personal_tasks) {
                    if (personal_task <= 0) {
                        personal_task = mark;
                        cout << "Студент - " << tempStudent->first_name << " получил отметку - " << mark << endl;
                        break;
                    }
                }
                tempStudent->averageMark = tempStudent->getAverageMark();
                fwrite(tempStudent, sizeof(struct student), 1, file);
            }
        }

        delete tempStudent;
        delete[] allStudent;
        fclose(file);
    } else {
        cout << "В этом файле нет такого студента\n";
    }
    return;
}

void printStudentLintByGroupFromAverageMark(FILE *file) {
    char fileName[max_length];
    int countOfStudent = 0;
    setFilename(fileName);

    student *temp = new student; //
    fopen_s(&file, fileName, "rb");
    while (fread(temp, sizeof(struct student), 1, file)) {
        countOfStudent++;
    }
    fclose(file);
    cout << "В этом файле есть " << countOfStudent << " студентов\n";

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

    for (int i = 0; i < countOfStudent; i++) {
        if (currentGroup == allStudent[i]->group_number && averageMarkFromGroup < allStudent[i]->averageMark) {
            cout << allStudent[i]->first_name << "\tсредний балл:" << allStudent[i]->averageMark << endl;
        }
    }
}


void readStructFromFile(FILE *file, char* fileName) {
    fopen_s(&file, fileName, "rb");
    if (file == nullptr) {
        system("cls");
        cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << fileName << "\033[0m"
             << endl;
        consolePause();
        return;
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
            for (int j = 0; j < max_length; j++) {
                if (temp->marks[i][j] > 0) {
                    cout << temp->marks[i][j] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\t\tИндивидуальные задания: ";
        for (int personal_task : temp->personal_tasks) {
            if (personal_task > 0) {
                cout << personal_task << " ";
            }
        }
        cout << "\n";
    }
    delete temp;
    fclose(file);
    consolePause();
    system("cls");
}

void writeBinaryDataAsText(FILE *file) {
    char fileName[max_length + 4];
    int countStudent = 0;

    setFilename(fileName);
    strcat_s(fileName, ".txt");
    student *temp = new student; //
    fopen_s(&file, fileName, "rb");
    while (fread(temp, sizeof(struct student), 1, file)) {
        countStudent++;
    }
    fclose(file);
    cout << "В это файле есть данные " << countStudent << " студентов\n";

    auto allStudent = new student *[countStudent];
    for (int i = 0; i < countStudent; i++) {
        allStudent[i] = new student;
    }
    fopen_s(&file, fileName, "rb");
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
            for (int k = 0; k < max_length; k++) {
                if (allStudent[i]->marks[g][k] > 0) {
                    fprintf_s(file, "%d ", allStudent[i]->marks[g][k]);
                }
            }
            fprintf_s(file, "\n");
        }
        fprintf_s(file, "\t\tИндивидуальные задания: ");
        for (int z = 0; z < 10; z++) {
            if (allStudent[i]->personal_tasks[z] > 0) {
                fprintf_s(file, "%d ", allStudent[i]->personal_tasks[z]);
            }
        }
        fprintf_s(file, "\n");
    }
    fclose(file);
}

int writeStructInFile(FILE *file) {
    int i;
    cout << "\nВведите колличество студентов, для добавления в файл:";
    cin >> i;
    for (int x = 0; x < i; x++) {
        auto *temp = new student;
        addInformationToStudent(temp);
        fwrite(temp, sizeof(struct student), 1, file);

    }
    return 1;
}

void consolePause() {
    system("pause");
    cin.get();
}

int getCountOfStudentFromFile(FILE *file, char *fileName) {
    student *tempStudent = new student;
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
