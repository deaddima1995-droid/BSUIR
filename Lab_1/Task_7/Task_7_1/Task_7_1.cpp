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

struct Student {
    char firstName[15];
    int groupNumber;
    int marks[3][20];
    int personalTasks[3][10];
};

void readStructFromFile(FILE* file);
int writeStructInFile(FILE* file);
int menu();
int subMenuOpenFile();
void createFile();
void addInformationToStudent(Student student);



int main() {
    while (true) {
    MainMenu:
        
        switch (menu()) {

        case 1: {           // Create File
            char name[20];
            cout << "Write file name:";
            cin >> name;
            if ((fopen_s(&file, name, "wb+")) == NULL) {
                writeStructInFile(file);
                cout << "File " << name << " was created";
            }
            fclose(file);
            break;
        }

        case 2: // Sub menu Open File
            
            while (true) {
            SubMenu2:
                switch (subMenuOpenFile()) {
                case 1: {                               // Read file
                    char name[20];
                    cout << "Write file name:";
                    cin >> name;
                    fopen_s(&file, name, "rb");
                    readStructFromFile(file);
                    fclose(file);
                    break;
                }
                case 2: {                               // Add Student to file
                    Student student;
                    cout << "Write name of student:";
                    cin >> student.firstName;
                    cout << "Write number group:";
                    cin >> student.groupNumber;
                    for (size_t counter = 0; counter < 3; counter++) {
                        int countOfMarks;
                        switch (counter) {
                        case 0: cout << "Write count marks of phisics:"; break;
                        case 1: cout << "Write count marks of mathematics:"; break;
                        case 2: cout << "Write count marks of informatics:"; break;
                        }
                        cin >> countOfMarks;
                        for (int i = 0; i < countOfMarks; i++) {
                            cin >> student.marks[counter][i];
                        }
                    }

                    char name[20];
                    cout << "Write file name:";
                    cin >> name;
                    fopen_s(&file, name, "ab");
                    fwrite(&student, sizeof(struct Student), 1, file);
                    fclose(file);
                    
                    break;
                }
                case 3: break;
                case 0: {                               // Exit
                    system("cls");
                    goto MainMenu; 
                    break;
                }
                default:
                    break;
                }
            }

        case 0: return 0;
        default: puts("Write correct number!\n");
        }
    } 
}


int menu() {
    cout << "-----Menu-----\n";
    cout << "1. Create File\n";
    cout << "2. Open File\n";
    cout << "0. Close program\n";
    int out;
    cin >> out;
    return out;
}

int subMenuOpenFile()
{   
    cout << "-----Menu-----\n--Open File:--\n";
    cout << "1. Read student's list\n";
    cout << "2. Add student to list\n";
    cout << "3. make personal task for student\n";
    cout << "0. Exit to main menu\n";
    int out;
    cin >> out;
    return out;
}

void createFile() {
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

void addInformationToStudent(Student student) {
    cout << "Write name of student:";
    cin >> student.firstName;
    cout << "Write number group:";
    cin >> student.groupNumber;
    for (size_t counter = 0; counter < 3; counter++) {
        int countOfMarks;
        switch (counter) {
        case 0: cout << "Write count marks of phisics:"; break;
        case 1: cout << "Write count marks of mathematics:"; break;
        case 2: cout << "Write count marks of informatics:"; break;
        }
        cin >> countOfMarks;
        for (int i = 0; i < countOfMarks; i++) {
            cin >> student.marks[counter][i];
        }
    }
}


void readStructFromFile(FILE* file) {
    Student temp;
    while (fread(&temp, sizeof(struct Student), 1, file)) {
        printf("Student's name - %s, group - %d\n", temp.firstName, temp.groupNumber);
    }
}

int writeStructInFile(FILE* file) {
    int i;
    cin >> i;
    for (int x = 0; x < i; x++) {
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
