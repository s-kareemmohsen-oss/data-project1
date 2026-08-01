#include "Node.h"
#include <iostream>
using namespace std;
template <typename T>
class PriorityQueue {
private:
    Node<T>* head;
    int queueSize;

    template <typename U>
    bool higherPriority(const U& a, const U& b) const {
        return a > b;
    }

    template <typename U>
    bool higherPriority(U* a, U* b) const {
        if (a == nullptr) return false;
        if (b == nullptr) return true;
        return *a > *b;
    }



public:
    PriorityQueue() : head(nullptr), queueSize(0) {}

    ~PriorityQueue() {
        clear();
    }

    PriorityQueue(const PriorityQueue& other) : head(nullptr), queueSize(0) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            push(current->getData());
            current = current->getNext();
        }
    }

    PriorityQueue& operator=(const PriorityQueue& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other.head;
            while (current != nullptr) {
                push(current->getData());
                current = current->getNext();
            }
        }
        return *this;
    }

    int size() const { return queueSize; }
    bool empty() const { return queueSize == 0; }

    void clear() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (empty() || higherPriority(value, head->getData())) {
            newNode->setNext(head);
            head = newNode;
        }
        else {
            Node<T>* current = head;
            while (current->getNext() != nullptr && !higherPriority(value, current->getNext()->getData())) {
                current = current->getNext();
            }
            newNode->setNext(current->getNext());
            current->setNext(newNode);
        }
        queueSize++;
    }

    void pop() {
        if (empty()) return;

        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        queueSize--;
    }

    const T& top() const {
        return head->getData();
    }

    void print() const {
        Node<T>* current = head;
        std::cout << "[ ";
        while (current != nullptr) {
            std::cout << current->getData() << (current->getNext() ? " -> " : "");
            current = current->getNext();
        }
        std::cout << " ] (Size: " << queueSize << ")\n";
    }
};