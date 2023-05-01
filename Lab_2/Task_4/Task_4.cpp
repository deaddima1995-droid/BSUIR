/*�������� ��������� �� ��������, ���������� (� ������, � �����),
  ��������� (� ������, � �����) � ������� ����������� � ���������� 3.3 ������ ��� ��������������� �������� �������.
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
int getRandomNumber(int min, int max);


int main() {
    srand(time(nullptr));
    system("chcp 1251");
    system("cls");

    auto *queue = new Queue();
    int menu{};
    // Menu
    while(true) {
        cout << "1. �������\n" <<
                "2. �������� � ������\n" <<
                "3. �������� � �����\n" <<
                "4. �������� � ������\n" <<
                "5. �������� � �����\n" <<
                "6. �������\n" <<
                "7. ������� ������������ �������\n" <<
                "0. �����\n";
        cin >> menu;
        switch (menu) {
            case 1: {
                if (queue) {
                    delAll(*queue);
                }
                queue = nullptr;
                int iter = getRandomNumber(0,20);
                for (int i = 0; i < iter; ++i) {
                    addInFront(queue, getRandomNumber(-15,15));
                }
                system("cls");
                break;
            }
            case 2: {
                int value;
                cout << "������� ��������:";
                cin >> value;
                addInFront(queue, value);
                break;
            }
            case 3: {
                int value;
                cout << "������� ��������:";
                cin >> value;
                addInEnd(queue, value);
                break;
            }
            case 4: {
                printFromFront(queue);
                break;
            }
            case 5: {
                printFromEnd(queue);
                break;
            }
            case 6: {
                
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