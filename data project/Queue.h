#include "Node.h"
#include <iostream>
#pragma once
using namespace std;
template<typename T>
class Queue {
private:
    Node<T>* frontNode;
    Node<T>* backNode;
    int queueSize;

public:
    Queue() : frontNode(nullptr), backNode(nullptr), queueSize(0) {}

    ~Queue() {
        clear();
    }

    Queue(const Queue& other) : frontNode(nullptr), backNode(nullptr), queueSize(0) {
        Node<T>* current = other.frontNode;
        while (current != nullptr) {
            enqueue(current->getData());
            current = current->getNext();
        }
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            Node<T>* current = other.frontNode;
            while (current != nullptr) {
                enqueue(current->getData());
                current = current->getNext();
            }
        }
        return *this;
    }
    int size() const { return queueSize; }
    bool empty() const { return queueSize == 0; }

    void clear() {
        while (!empty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (empty()) {
            frontNode = backNode = newNode;
        }
        else {
            backNode->setNext(newNode);
            backNode = newNode;
        }
        queueSize++;
    }

    void dequeue() {
        if (empty()) return;

        Node<T>* temp = frontNode;
        frontNode = frontNode->getNext();
        delete temp;
        queueSize--;

        if (frontNode == nullptr) {
            backNode = nullptr;
        }
    }

    const T& front() const {
        return frontNode->getData();
    }

    const T& back() const {
        return backNode->getData();
    }

    void print() const {
        Node<T>* current = frontNode;
        cout << "[ ";
        while (current != nullptr) {
            std::cout << current->getData() << (current->getNext() ? " -> " : "");
            current = current->getNext();
        }
        cout << " ] (Size: " << queueSize << ")\n";
    }
};