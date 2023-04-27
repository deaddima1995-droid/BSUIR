/*Написать программу по созданию, добавлению, просмотру и решению приведенных далее задач (в рассмотренных примерах это действие отсутствует)
    для однонаправленного линейного списка типа Stack. Реализовать сортировку стека методами, рассмотренными в подразделе 3.1.
    -Решение поставленной задачи описать в виде блок-схемы.
    Во всех заданиях создать список из положительных и отрицательных случайных целых чисел.
    В созданном списке определить максимальное значение и удалить его.
*/

#include <iostream>

using namespace std;

struct   Stack {
    int  info;
    Stack   *next;
};

Stack *addToStack(Stack *pStack, int number);
Stack *getStack(Stack *pStack, int *out);
void show (Stack *);
void delAll(Stack **);
void del(Stack *);
void consolePause();
void selectionSort(Stack *pStack);
void quickSort(Stack *pStack);
int getRandomNumber(int min, int max);

int main() {
    srand(time(nullptr));
    system("chcp 1251");
    Stack *bStack = nullptr;
    int menu{};
    // Menu
    while(true) {
        cout << "1. Создать\n" <<
             "2. Добавить\n" <<
             "3. Просмотр\n" <<
             "4. Удалить\n" <<
             "0. Выход\n";
        cin >> menu;
        switch (menu) {
            case 1: { // Создать стек из случайных чисел
                delAll(&bStack);
                bStack = nullptr;
                int count = getRandomNumber(1,15);
                for (int i = 0; i < count; ++i) {
                    bStack = addToStack(bStack, getRandomNumber(-30,30));
                }
                consolePause();
                break;
            }
            case 2: { // Добавить данные в стек
                int number;
                cout << "Введите число: ";
                cin >> number;
                bStack = addToStack(bStack,number);
                consolePause();
                break;
            }
            case 3: { // Просмотр стека
                cout << "Данные стека:\n";
                show(bStack);
                cout << endl;
                consolePause();
                break;
            }
            case 4: {
                delAll(&bStack);
                cout << "Стек удален\n";
            }
            case 5: { // Сортировка выбором

                break;
            }
            case 0: {
                return 1;
            }
            default: {
                return -1;
            }
        }
        system("cls");
    }
}

Stack *addToStack (Stack *pStack, int number){
    auto *temp = new Stack;
    temp -> info = number;
    temp -> next = pStack;
    return temp;
}

Stack *getStack(Stack *pStack, int *out) {
    Stack *temp = pStack;
    *out = pStack->info;
    pStack = pStack->next;
    delete temp;
    return pStack;
}

void show (Stack *pStack){
    while (pStack != nullptr){
        cout << pStack -> info << "\t";
        pStack = pStack -> next;
    }
}

void delAll(Stack **stack) {
    Stack *temp;
    while (*stack != nullptr) {
        temp = *stack;
        *stack = (*stack)->next;
        delete temp;
    }
}

void consolePause() {
    system("pause");
    cin.get();
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

void selectionSort(Stack *pStack) {
    Stack tmp;

    int count = 0;
    Stack *curr = pStack->next;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
}




