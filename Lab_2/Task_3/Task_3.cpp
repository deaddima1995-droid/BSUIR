/*Написать программу по созданию, добавлению, просмотру и решению приведенных далее задач (в рассмотренных примерах это действие отсутствует)
    для однонаправленного линейного списка типа Stack. Реализовать сортировку стека методами, рассмотренными в подразделе 3.1.
    Решение поставленной задачи описать в виде блок-схемы.
    Во всех заданиях создать список из положительных и отрицательных случайных целых чисел.
    В созданном списке определить максимальное значение и удалить его.
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
    for (int i = 0; i < 10; ++i) {
        bStack = addToStack(bStack, getRandomNumber(0,10));
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




