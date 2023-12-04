#include "Queue.h"
#include "Except.h"
#include <iostream>
using namespace std;

template <typename T>
Queue<T>::Node::Node(T data) {
    this->data = data;
    this->next = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
    while(!isEmpty()) {
        dequeue();
    }
}

template <typename T>
bool Queue<T>::isEmpty() {
    return head == nullptr;
}

template <typename T>
void Queue<T>::enqueue(T data) {
    Node *newNode = new Node(data);
    if(newNode == nullptr) {
        throw Except("Internal error: Can not allocate memory for new node");
    }
    if(newNode == nullptr) {
        throw Except("Can not allocate more memory in enqueue operations");
    }
    if(head == nullptr) {
        head = tail = newNode;
    } else {
        tail = tail->next = newNode;
    }
}

template <typename T>
T Queue<T>::dequeue() {
    if(head == nullptr) {
        throw Except("Attempt to dequeue empty queue");
    }

    T output = head->data;
    Node *tmp = head;
    head = head->next;
    delete tmp;

    return output;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& queue) {
    Node *tmp = queue.head;
    while(tmp != nullptr) {
        enqueue(tmp->data);
        tmp = tmp -> next;
    }
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue) {
    while(!isEmpty()) dequeue();

    Node *tmp = queue.head;
    while(tmp != nullptr) {
        enqueue(tmp->data);
        tmp = tmp -> next;
    }

    return *this;
}

template class Queue<int>;
template class Queue<char>;
