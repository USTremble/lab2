#ifndef LR2_QUEUE_H
#define LR2_QUEUE_H

#include "dlist.h"
#include <iostream>

using namespace std;

template <typename T>
struct Queue {
    Dlist<T> list; // список для хранения элементов очереди

    Dlist<T> data() const;
    int size() const;
    void enqueue(const T& val);
    T dequeue();
    void print() const;

    Queue() {}
};

template <typename T>
Dlist<T> Queue<T>::data() const {
    return list; // возвращаем внутренний список
}

template <typename T>
int Queue<T>::size() const {
    return list.size(); // возвращаем размер списка
}

template <typename T>
void Queue<T>::enqueue(const T& val) {
    list.pushBack(val); // добавляем элемент в конец списка
}

template <typename T>
T Queue<T>::dequeue() {
    if (size() == 0) {
        throw runtime_error("Queue is empty");
    }
    T dequeuedValue = list.head->value; // сохраняем значение из начала
    list.removeForward();
    return dequeuedValue;
}

template <typename T>
void Queue<T>::print() const {
    for (int i = 0; i < size(); i++) {
        cout << list.get(i) << " ";
    }
}

template <typename T>
ostream& operator<<(ostream& os, const Queue<T>& queue) {
    queue.print();
    return os;
}

#endif //LR2_QUEUE_H
