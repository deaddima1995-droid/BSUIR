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
Stack *getStack(Stack *pStack, int *out);
void show (Stack *);
void delAll(Stack **);
void del(Stack *);
void consolePause();
void selectionSort(Stack *pStack);
void quickSort(Stack *pStack);

void push(Stack** top, int data);

int getRandomNumber(int min, int max);
int pop(Stack** top);
int peek(Stack* top);
bool isEmpty(Stack* top);
void quickSortStackUtil(Stack** top, Stack** end);
void quickSortStack(Stack** top);
void push(Stack** top, int data);



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
                "5. Сортировка выбором\n" <<
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
                selectionSort(bStack);
                break;
            }
            case 6: { // Quick sort
                quickSortStack(&bStack);
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
    Stack *tmp = pStack;
    Stack *iter;
    int data;
    do {
        for (iter = pStack; iter->next != tmp; iter = iter->next) {
            if (iter->next == nullptr) break;
            if (iter->info > iter->next->info) {
                data = iter->info;
                iter->info = iter->next->info;
                iter->next->info = data;
            }
        }
        tmp = iter;
    } while (iter != pStack);
}

void quickSort(Stack *pStack) {

}

void push(Stack** top, int data) {
    Stack* new_node = new Stack;
    new_node->info = data;
    new_node->next = *top;
    *top = new_node;
}

int pop(Stack** top) {
    if (*top == nullptr) {
        return INT_MAX;
    }
    int data = (*top)->info;
    Stack* temp = *top;
    *top = (*top)->next;
    delete temp;
    return data;
}

int peek(Stack* top) {
    if (top == nullptr) {
        return INT_MAX;
    }
    return top->info;
}

bool isEmpty(Stack* top) {
    return top == nullptr;
}

Stack* partition(Stack** top, Stack** end, int pivot) {
    Stack* current = *top;
    Stack* prev = nullptr;
    while (current != *end) {
        if (current->info < pivot) {
            if (*top == current) {
                *top = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = nullptr;
            push(top, current->info);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return prev;
}

void quickSortStack(Stack** top) {
    if (*top == nullptr) {
        return;
    }
    Stack* end = *top;
    while (end->next != nullptr) {
        end = end->next;
    }
    quickSortStackUtil(top, &end);
}

void quickSortStackUtil(Stack** top, Stack** end) {
    if (*top != *end) {
        int pivot = pop(end);
        Stack* partition_point = partition(top, end, pivot);
        push(&partition_point->next, pivot);
        quickSortStackUtil(top, &partition_point);
        quickSortStackUtil(&partition_point->next, end);
    }
}



