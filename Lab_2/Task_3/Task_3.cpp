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
} ;

Stack * addToStack(Stack *, int number);
void Show (Stack *);
void DelAll(Stack **);
Stack * Task5 (Stack *);
int getRandomNumber(int min, int max);

int main() {
    srand(time(nullptr));
    Stack *bStack = nullptr;
    for (int i = 0; i < 10; ++i) {
        bStack = addToStack(bStack, getRandomNumber(0,10));
    }
    Show(bStack);
    system("pause");
    cin.get();
}

Stack * addToStack (Stack *b, int number){
    Stack * temp = new Stack;
    temp -> info = number;
    temp -> next = b;
    return temp;
}

void Show (Stack *pStack){
    while (pStack != nullptr){
        cout << pStack -> info << endl;
        pStack = pStack -> next;
    }
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}



