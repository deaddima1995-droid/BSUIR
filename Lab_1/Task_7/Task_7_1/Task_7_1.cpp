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

constexpr int max_length = 20;

FILE* file;

struct student {
    char first_name[15];
    int group_number;
    int marks[3][20];
    int personal_tasks[10];
    
    static double getAverageMark(){

        return 0;
    }
    
};

void readStructFromFile(FILE* file);
int writeStructInFile(FILE* file);
int menu();
int subMenuOpenFile();
void addInformationToStudent(student *student);
void setFilename(char* name);
int makePeronalTask();


int main() {
    while (true) {
    MainMenu:
        
        switch (menu()) {

        case 1: {           // Create File
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
            
            while (true) {
            
                switch (subMenuOpenFile()) {
                case 1: {                               // Read file
                    char* name = new char[max_length];
                    setFilename(name);

                    if (fopen_s(&file, name, "rb") != NULL) {
	                    cout << "File can't read";
                    }
                    system("cls");
                    readStructFromFile(file);
                    fclose(file);
                    delete[] name;
                    break;
                }
                case 2: {                               // Add student to file
                    char* name = new char[max_length];
                	auto *temp = new student;

                    setFilename(name);
                    addInformationToStudent(temp);
                    system("cls");

                    fopen_s(&file, name, "ab");
                    if (fwrite(temp, sizeof(struct student), 1, file) != NULL) {
                        cout << "Student: " << temp->first_name << " was added to file " << name << endl;
                    }
                    else {
                        cout << "Error student don't added to file";
                    }
                    fclose(file);
                    delete temp;
                    delete name;
                    break;
                }
                case 3: makePeronalTask(); break;
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
    system("cls");
    return out;
}

int subMenuOpenFile() {   
    cout << "--Open File:--\n";
    cout << "1. Read student's list\n";
    cout << "2. Add student to list\n";
    cout << "3. make personal task for student\n";
    cout << "0. Exit to main menu\n";
    int out;
    cin >> out;
    return out;
}

void addInformationToStudent(student *student) {
    cout << "Write name of student:";
    cin >> student->first_name;
    cout << "Write number group:";
    cin >> student->group_number;
    for (size_t counter = 0; counter < 3; counter++) {
        int countOfMarks;
        switch (counter) {
        case 0: cout << "Write count marks of physics:"; break;
        case 1: cout << "Write count marks of mathematics:"; break;
        case 2: cout << "Write count marks of informatics:"; break;
        }
        cin >> countOfMarks;
        for (int i = 0; i < countOfMarks; i++) {
            cin >> student->marks[counter][i];
        }
    }
}

void setFilename(char* name) {
    cout << "Write file name:";
    cin >> name;
}

int makePeronalTask() {
    int countStudent = 0;
    
    char name[max_length];
    setFilename(name);

    student *temp = new student; //
    fopen_s(&file, name, "rb");
    while (fread(temp, sizeof(struct student), 1, file)) {
        countStudent++;
    }
    fclose(file);
    cout << "This file has " << countStudent << " student's\n";

    auto allStudent = new student*[countStudent];
    for (int i = 0; i < countStudent; i++) {
        allStudent[i] = new student;
    }

    student *temp_s_student = new student;
    cout << "Write name student:";
    cin >> temp_s_student->first_name;
    cout << "Write group student:";
    cin >> temp_s_student->group_number;
    string s1;
    s1 = temp_s_student->first_name;
    

    fopen_s(&file, name, "rb");
    for (int i = 0; i < countStudent; i++) {
        fread(allStudent[i], sizeof(struct student), 1, file);
        string s2 = allStudent[i]->first_name;
        if (s1 == s2 && allStudent[i]->group_number == temp_s_student->group_number) {
            cout << "we have student: " << temp_s_student->first_name << "\t" << temp_s_student->group_number << endl;
        }
    }
    fclose(file);
    

    return 0;
}


void readStructFromFile(FILE* file) {
    student temp;
    while (fread(&temp, sizeof(struct student), 1, file)) {
        cout << "Student name - " << temp.first_name << "\tGroup - " << temp.group_number << endl;
        cout << "\tMarks:\n";
        for (int i = 0; i < 3; i++) {
	        if (i == 0) {
                cout << "\t\tPhysics: ";
	        } else if (i == 1) {
                cout << "\t\tMathematics: ";
	        } else if (i == 2) {
                cout << "\t\tInformatics: ";
	        }
            for (int j = 0; j < max_length; j++) {
	            if (temp.marks[i][j] > 0) {
                    cout << temp.marks[i][j] << " ";
	            }
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int writeStructInFile(FILE* file) {
    int i;
    cout << "\nWrite number count of student:";
    cin >> i;
    for (int x = 0; x < i; x++) {
        auto *temp = new student;
        addInformationToStudent(temp);
        fwrite(temp, sizeof(struct student), 1, file);
        delete temp;
    }
    return 1;
}
