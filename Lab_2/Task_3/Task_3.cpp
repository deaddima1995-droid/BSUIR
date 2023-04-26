/*Ќаписать программу по созданию, добавлению, просмотру и решению приведенных далее задач (в рассмотренных примерах это действие отсутствует)
    дл€ однонаправленного линейного списка типа Stack. –еализовать сортировку стека методами, рассмотренными в подразделе 3.1.
    –ешение поставленной задачи описать в виде блок-схемы.
    ¬о всех задани€х создать список из положительных и отрицательных случайных целых чисел.
    ¬ созданном списке определить максимальное значение и удалить его.
*/

#include <iostream>

using namespace std;

struct   Stack {
    int  info;
    Stack   *next;
};

Stack *addToStack(Stack*, int number);
Stack *getStack(Stack*, int*);

void Show (Stack *);
void delAll(Stack **);
void del(Stack *);
Stack * Task5 (Stack *);
int getRandomNumber(int min, int max);

int main() {
    srand(time(nullptr));
    system("chcp 1251");
    Stack *bStack = nullptr;
    int menu{};
    // Menu

    cout << "1. —оздать\n" <<
            "2. ƒобавить\n" <<
            "3. ѕросмотр\n" <<
            "4. ”далить\n" <<
            "0. ¬ыход\n";
    cin >> menu;
    switch (menu) {
        case 1: {
            break;
        }
        case 0: {
            return 1;
        }
    }

    for (int i = 0; i < 10; ++i) {
        bStack = addToStack(bStack, getRandomNumber(-10,10));
    }
    Show(bStack);
    system("pause");
    cin.get();
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

void Show (Stack *pStack){
    while (pStack != nullptr){
        cout << pStack -> info << endl;
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

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}




