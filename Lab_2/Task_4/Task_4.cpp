/*Ќаписать программу по созданию, добавлению (в начало, в конец),
  просмотру (с начала, с конца) и решению приведенной в подразделе 3.3 задачи дл€ двунаправленных линейных списков.
 */
#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node *prev;
};
struct Queue {
    Node *front;
    Node *end;
    Queue() {
        front = nullptr;
        end = nullptr;
    }
};
void addInEnd(Queue *queue, int value);
void addInFront(Queue *queue, int value);
void printFromFront(Queue *queue);
void printFromEnd(Queue *queue);
void consolePause();
void delAll(Queue &queue);
void delByKey(Queue& queue, int key);
int getRandomNumber(int min, int max);


int main() {
    srand(time(nullptr));
    system("chcp 1251");
    //system("cls");

    auto *queue = new Queue();
    int menu{};
    // Menu
    while(true) {
        system("cls");
        cout << "1. —оздать\n" <<
                "2. ƒобавить в начало\n" <<
                "3. ƒобавить в конец\n" <<
                "4. ѕросмотр с начала\n" <<
                "5. ѕросмотр с конца\n" <<
                "6. ”далить максимальный элемент\n" <<
                "0. ¬ыход\n";
        cin >> menu;
        switch (menu) {
            case 1: {
                delAll(*queue);
                delete queue;
                queue = new Queue();
                int iter = getRandomNumber(0,20);
                for (int i = 0; i < iter; ++i) {
                    addInFront(queue, getRandomNumber(-15,15));
                }
                system("cls");
                break;
            }
            case 2: {
                int value;
                cout << "¬ведите значение:";
                cin >> value;
                addInFront(queue, value);
                break;
            }
            case 3: {
                int value;
                cout << "¬ведите значение:";
                cin >> value;
                addInEnd(queue, value);
                break;
            }
            case 4: {
                printFromFront(queue);
                consolePause();
                break;
            }
            case 5: {
                printFromEnd(queue);
                consolePause();
                break;
            }
            case 6: {
                int max = INT32_MIN;
                Node *tmp = queue->front;
                while (tmp) {
                    if (tmp->data > max) {
                        max = tmp->data;
                    }
                    tmp = tmp->next;
                }
                    delByKey(*queue, max);
                break;
            }
            default: {
                return 1;
            }
        }
    }
}

void addInFront(Queue *queue, int value) {
    Node *tmp = new Node;
    tmp->data = value;
    tmp->next = queue->front;
    tmp->prev = nullptr;

    if (queue->front == nullptr) {
        queue->front = queue->end = tmp;
    } else {
        queue->front->prev = tmp;
        queue->front = tmp;
    }
}
void addInEnd(Queue *queue, int value) {
    Node *tmp = new Node;
    tmp->data = value;
    tmp->next = nullptr;
    tmp->prev = queue->end;

    if (queue->front == nullptr) {
        queue->front = queue->end = tmp;
    } else {
        queue->end->next = tmp;
        queue->end = tmp;
    }
}
void printFromFront(Queue *queue) {
    Node *current = queue->front;
    while (current != nullptr) {
        cout << current->data << "\t";
        current = current->next;
    }
    cout << endl;
}

void printFromEnd(Queue *queue) {
    Node *current = queue->end;
    while (current != nullptr) {
        cout << current->data << "\t";
        current = current->prev;
    }
    cout << endl;
}

void consolePause() {
    system("pause");
    cin.get();
}

void delByKey(Queue& queue, int key) {
    Node* current = queue.front;
    // перебираем все узлы
    while (current != nullptr) {
        // если найденный узел содержит значение, которое мы ищем
        if (current->data == key) {
            // если найденный узел - единственный элемент в очереди
            if (current == queue.front && current == queue.end) {
                queue.front = queue.end = nullptr;
            }
                // если найденный узел €вл€етс€ первым элементом очереди
            else if (current == queue.front) {
                queue.front = current->next;
                queue.front->prev = nullptr;
            }
                // если найденный узел €вл€етс€ последним элементом очереди
            else if (current == queue.end) {
                queue.end = current->prev;
                queue.end->next = nullptr;
            }
                // если найденный узел находитс€ в середине очереди
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            // освобождаем пам€ть, выделенную дл€ удал€емого узла
            delete current;
            break; // ¬ыходим из функции, т.к. только первое вхождение будет удалено
        }
        current = current->next; // переходим к следующему узлу
    }
}

void delAll(Queue &queue) {
    Node* current = queue.front;
    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    queue.front = queue.end = nullptr;
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}