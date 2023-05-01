/*Написать программу по созданию, добавлению (в начало, в конец),
  просмотру (с начала, с конца) и решению приведенной в подразделе 3.3 задачи для двунаправленных линейных списков.

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
void print(Queue *queue);
void consolePause();

int main() {
    srand(time(nullptr));
    system("chcp 1251");
    system("cls");

    auto *queue = new Queue();
    addInFront(queue,10);
    addInFront(queue,9);
    addInFront(queue,8);
    addInEnd(queue, 11);

    print(queue);
    consolePause();
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
void print(Queue *queue) {
    Node *current = queue->front;
    while (current != nullptr) {
        cout << current->data << "\t";
        current = current->next;
    }
    cout << endl;
}

void consolePause() {
    system("pause");
    cin.get();
}