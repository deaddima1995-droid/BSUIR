 /*Написать программу обработки файла записей, 
содержащую следующие пункты меню: «Создание», «Просмотр», «Добавление», «Решение индивидуального задания».
Каждая запись должна содержать следующую информацию о студентах:
– фамилия; +
– номер группы; +
– оценки за семестр: по физике, математике, информатике; +
– средний балл. +
Организовать ввод исходных данных, средний балл рассчитать по введенным оценкам. +
Содержимое всего файла и результаты решения индивидуального задания записать в текстовый файл. +

13. Вычислить общий средний балл студентов интересующей вас группы и распечатать список студентов этой группы,  -
имеющих средний балл выше общего.
*/
#include <iostream>

using namespace std;


constexpr int max_length = 20;

FILE* file;

struct student {
    char first_name[15];
    int group_number;
    int marks[3][20];
    int personal_tasks[10];
    double averageMark = 0;
    
    double getAverageMark(){
        int countMarks = 0;
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            for (int g = 0; g < 20; g++) {
                if (marks[i][g] > 0) {
                    sum += marks[i][g];
                    countMarks++;
                }
            }
        }
        for (int i = 0; i < 10; i++) {
            if (personal_tasks[i] > 0) {
                sum += personal_tasks[i];
                countMarks++;
            }
        }
        return (countMarks == 0) ? 0 : sum / (countMarks * 1.0);
    }
    
};

void readStructFromFile(FILE* file);
void writeBinaryDataAsText(FILE* file);
int writeStructInFile(FILE* file);
int menu();
int subMenuOpenFile();
void addInformationToStudent(student *student);
void setFilename(char* name);
int makePeronalTask();
void printStudentLintByGroupFromAverageMark(FILE* file);


int main() {
    system("chcp 1251");
    system("cls");
    while (true) {
    MainMenu:   
        switch (menu()) {

        case 1: {                                       // Создать бинарный файл
            char* name = new char[20];
            setFilename(name);
            if (fopen_s(&file, name, "wb+") == NULL) {
                writeStructInFile(file);
                system("cls");
                cout << "File " << name << " was created\n";
            }
            fclose(file);
            delete[] name;
            break;
        }

        case 2: // Sub menu Open File
         SubMenu:   
            while (true) {
            
                switch (subMenuOpenFile()) {
                case 1: {                               // Вывести на экран данные из бинарного файла
                    char* name = new char[max_length];
                    setFilename(name);
                    fopen_s(&file, name, "rb");
                    if (file == NULL) {
                        system("cls");
                        cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << name << "\033[0m" << endl;
                        system("pause");
                        cin.get();
                        break;
                    }
                    system("cls");
                    cout << "\033[32mОткрыт файл: " << name << "\033[0m" << endl;
                    readStructFromFile(file);
                    system("pause");
                    cin.get();
                    fclose(file);    
                    delete[] name;
                    break;
                }
                case 2: {                               // Добавить студента в бинарный файл
                    char* name = new char[max_length];
                	auto *temp = new student;

                    setFilename(name);
                    fopen_s(&file, name, "ab");
                    if (file == NULL) {
                        system("cls");
                        cout << "\033[31m" << "Ошибка открытия файла: " << "\033[32m" << name << "\033[0m" << endl;
                        system("pause");
                        cin.get();
                        break;
                    }


                    addInformationToStudent(temp);
                    system("cls");

                    
                    if (fwrite(temp, sizeof(struct student), 1, file) != NULL) {
                        cout << "Студент: " << temp->first_name << " был добавлен в файл - " << name << endl;
                    }
                    else {
                        cout << "Ошибка, студент не был добавлен в файл";
                    }
                    fclose(file);
                    delete temp;
                    delete name;
                    break;
                }
                case 3: {                               // Выполнение "персонального" задания
                    system("cls");
                    makePeronalTask(); 
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

        case 0: return 0;                               // Выход из программы
        default: puts("Ошибка, введите номер пункта ->\n");
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
        case 0: cout << "Колличество оценок по физике:"; break;
        case 1: cout << "Колличество оценок по математике:"; break;
        case 2: cout << "Колличество оценок по информатике:"; break;
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

void setFilename(char* name) {
    cout << "Введите имя файла:";
    cin >> name;
}

int makePeronalTask() {
    int countOfStudent = 0;
    int equalStudent = -1;
    char name[max_length];
    setFilename(name);

    student *temp = new student;
    fopen_s(&file, name, "rb");
    while (fread(temp, sizeof(struct student), 1, file)) {
        countOfStudent++;
    }
    fclose(file);
    cout << "Этот файл содержит данные  " << countOfStudent << " студентов\n";

    auto allStudent = new student*[countOfStudent];
    for (int i = 0; i < countOfStudent; i++) {
        allStudent[i] = new student;
    }

    student *temp_s_student = new student;
    cout << "Имя студента:";
    cin >> temp_s_student->first_name;
    cout << "Номер группы:";
    cin >> temp_s_student->group_number;
    string s1;
    s1 = temp_s_student->first_name;
    

    fopen_s(&file, name, "rb");
    for (int i = 0; i < countOfStudent; i++) {
        fread(allStudent[i], sizeof(struct student), 1, file);
        string s2 = allStudent[i]->first_name;
        if (s1 == s2 && allStudent[i]->group_number == temp_s_student->group_number) {
            cout << "В файле есть такой студент: " << temp_s_student->first_name << "\t" << temp_s_student->group_number << endl;
            temp_s_student = allStudent[i];
            equalStudent = i;
        }
    }
    delete temp_s_student;
    delete[] allStudent;
    fclose(file);

    if (equalStudent != -1) {
        fopen_s(&file, name, "wb");
        for (int i = 0; i < countOfStudent; i++) {
            if (i != equalStudent) {
                fwrite(allStudent[i], sizeof(struct student), 1, file);
            } else {
                int mark = 0;
                cout << "Введите оценку за персональное задание:";
                cin >> mark;
                for (int g = 0; g < 10; g++) {
                    if (temp_s_student->personal_tasks[g] < 0) {
                        temp_s_student->personal_tasks[g] = mark;
                        break;
                    }
                }
                temp_s_student->personal_tasks[0] = 10;
                temp_s_student->averageMark = temp_s_student->getAverageMark();
                fwrite(temp_s_student, sizeof(struct student), 1, file);
            }
        }


        fclose(file);
    } else {
        cout << "В этом файле нет такого студента\n";
    }
    delete temp_s_student;
    delete[] allStudent;
    return 0;
}

void printStudentLintByGroupFromAverageMark(FILE* file) {
    char fileName[max_length];
    int countOfStudent = 0;
    setFilename(fileName);

    student* temp = new student; //
    fopen_s(&file, fileName, "rb");
    while (fread(temp, sizeof(struct student), 1, file)) {
        countOfStudent++;
    }
    fclose(file);
    cout << "В этом файле есть " << countOfStudent << " студентов\n";

    auto allStudent = new student * [countOfStudent];
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
    averageMarkFromGroup /= (double)countStudentFromGroup;
    cout << "Средняя оценка по группе  №" << currentGroup << " - " << averageMarkFromGroup << "баллов" << endl;
    
    for (int i = 0; i < countOfStudent; i++) {
        if (currentGroup == allStudent[i]->group_number && averageMarkFromGroup < allStudent[i]->averageMark) {
            cout << allStudent[i]->first_name << "\tсредний балл:" << allStudent[i]->averageMark << endl;
        }
    }
}


void readStructFromFile(FILE* file) {
    student temp;
    while (fread(&temp, sizeof(struct student), 1, file)) {
        cout << "Студент - " << temp.first_name << "\tГруппа - " << temp.group_number << "\tСредний балл - " << temp.averageMark << endl;
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
	            if (temp.marks[i][j] > 0) {
                    cout << temp.marks[i][j] << " ";
	            }
            }
            cout << "\n";
        }
        cout << "\t\tИндивидуальные задания: ";
            for (int  i = 0; i < 10; i++) {
                if (temp.personal_tasks[i] > 0) {
                    cout << temp.personal_tasks[i] << " ";
                }
            }
        cout << "\n";
    }
}

void writeBinaryDataAsText(FILE* file) {
    char fileName[max_length + 4];
    int countStudent = 0;

    setFilename(fileName);
    strcat_s(fileName, ".txt");
    student* temp = new student; //
    fopen_s(&file, fileName, "rb");
    while (fread(temp, sizeof(struct student), 1, file)) {
        countStudent++;
    }
    fclose(file);
    cout << "В это файле есть данные " << countStudent << " студентов\n";

    auto allStudent = new student * [countStudent];
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
        fprintf_s(file, "\tИмя - %s\t Группа - %d\t Средний балл - %.2lf\n", allStudent[i]->first_name, allStudent[i]->group_number, allStudent[i]->averageMark);
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

int writeStructInFile(FILE* file) {
    int i;
    cout << "\nВведите колличество студентов, для добавления в файл:";
    cin >> i;
    for (int x = 0; x < i; x++) {
        auto *temp = new student;
        addInformationToStudent(temp);
        fwrite(temp, sizeof(struct student), 1, file);
        delete temp;
    }
    return 1;
}
