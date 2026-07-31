#include "Node.h"
#include <iostream>
using namespace std;
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int listSize;

public:
    LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    ~LinkedList() {
        clear();
    }

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->getData());
            current = current->getNext();
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other.head;
            while (current != nullptr) {
                push_back(current->getData());
                current = current->getNext();
            }
        }
        return *this;
    }

    int size() const { return listSize; }
    bool empty() const { return listSize == 0; }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        listSize = 0;
    }

    const T& getFront() const {
        return head->getData();
    }

    const T& getBack() const {
        return tail->getData();
    }

    const T& getAt(int index) const {
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
        }
        return current->getData();
    }

    void pushfront(const T& value) {
        Node<T>* newNode = new Node<T>(value, head);
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
        listSize++;
    }

    void pushback(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (empty()) {
            head = tail = newNode;
        }
        else {
            tail->setNext(newNode);
            tail = newNode;
        }
        listSize++;
    }

    void insertAt(int index, const T& value) {
        if (index < 0 || index > listSize) return;

        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == listSize) {
            push_back(value);
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->getNext();
        }

        Node<T>* newNode = new Node<T>(value, current->getNext());
        current->setNext(newNode);
        listSize++;
    }

    void popfront() {
        if (empty()) return;

        Node<T>* temp = head;
        head = head->getNext();
        delete temp;
        listSize--;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void popback() {
        if (empty()) return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node<T>* current = head;
            while (current->getNext() != tail) {
                current = current->getNext();
            }
            delete tail;
            tail = current;
            tail->setNext(nullptr);
        }
        listSize--;
    }

    void removeAt(int index) {
        if (index < 0 || index >= listSize) return;

        if (index == 0) {
            pop_front();
            return;
        }
        if (index == listSize - 1) {
            pop_back();
            return;
        }

        Node<T>* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->getNext();
        }

        Node<T>* target = current->getNext();
        current->setNext(target->getNext());
        delete target;
        listSize--;
    }

    bool removeValue(const T& value) {
        if (empty()) return false;

        if (head->getData() == value) {
            pop_front();
            return true;
        }

        Node<T>* current = head;
        while (current->getNext() != nullptr && current->getNext()->getData() != value) {
            current = current->getNext();
        }

        if (current->getNext() != nullptr) {
            Node<T>* target = current->getNext();
            if (target == tail) {
                tail = current;
            }
            current->setNext(target->getNext());
            delete target;
            listSize--;
            return true;
        }

        return false;
    }

    int find(const T& value) const {
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->getData() == value) {
                return index;
            }
            current = current->getNext();
            index++;
        }
        return -1;
    }

    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;
        tail = head;

        while (current != nullptr) {
            next = current->getNext();
            current->setNext(prev);
            prev = current;
            current = next;
        }
        head = prev;
    }

    void print() const {
        Node<T>* current = head;
        cout << "[ ";
        while (current != nullptr) {
            cout << current->getData() << (current->getNext() ? " -> " : "");
            current = current->getNext();
        }
        cout << " ] (Size: " << listSize << ")\n";
    }
};