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
    Stack *next;
};

Stack *addToStack(Stack *pStack, int number);
void show (Stack *);
void delAll(Stack **);
Stack* del(Stack *);
void consolePause();
void sortFromInfo(Stack *pStack);
void sortFromAddress(Stack *&pStack);
int getRandomNumber(int min, int max);


int main() {
    srand(time(nullptr));
    system("chcp 1251");
    system("cls");
    Stack *bStack = nullptr;
    int menu{};
    // Menu
    while(true) {
        cout << "1. Создать\n" <<
                "2. Добавить\n" <<
                "3. Просмотр\n" <<
                "4. Удалить\n" <<
                "5. Сортировка по значению\n" <<
                "6. Сортировка по адресу\n" <<
                "7. Удалить максимальный элемент\n" <<
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
                bStack = del(bStack);
                cout << "Стек удален\n";
            }
            case 5: { // Сортировка по значению
                sortFromInfo(bStack);
                break;
            }
            case 6: { // Сортировка по адресу
                sortFromAddress(bStack);
                break;
            }
            case 7: {
                Stack **maxStack = &bStack;
                for (Stack **temp = &bStack; *temp; temp = &(*temp)->next)
                    if ((*temp)->info > (*maxStack)->info) {
                        maxStack = &(*temp);
                    }
                *maxStack = del(*maxStack);
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
void show (Stack *pStack){
    while (pStack != nullptr){
        cout << pStack -> info << "\t";
        pStack = pStack -> next;
    }
}
Stack* del(Stack *pStack) {
    if (pStack == nullptr) return nullptr;
    return pStack->next;
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

void sortFromInfo(Stack *pStack) {
    for(Stack *temp = pStack; temp; temp = temp->next) {
        for (Stack *nextTemp = temp->next; nextTemp; nextTemp = nextTemp->next) {
            if (temp->info > nextTemp->info) {
                int info = temp->info;
                temp->info = nextTemp->info;
                nextTemp->info = info;
            }
        }
    }
}

void sortFromAddress(Stack *&pStack) {
    pStack = addToStack(pStack, 0);
    for (Stack *temp = pStack; temp; temp = temp->next) {
        for (Stack *nextTemp = temp->next; nextTemp; nextTemp = nextTemp->next) {
            if (nextTemp->next && temp->next->info > nextTemp->next->info) {
                Stack *tStack = nextTemp->next;
                nextTemp->next = tStack->next;
                tStack->next = temp->next;
                temp->next = tStack;
                nextTemp = temp;
            }
        }
    }
    pStack = del(pStack);
}



