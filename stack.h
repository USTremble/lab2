#ifndef LR2_STACK_H
#define LR2_STACK_H

#include "slist.h"

template <typename T>
struct Stack {
    SList<T> list;

    int size() const;
    SList<T> data() const;
    void push(const T& value);
    T pop();
    void print() const;

    Stack() {}
};

template <typename T>
int Stack<T>::size() const {
    return list.size();
}

template <typename T>
SList<T> Stack<T>::data() const {
    return list;
}

template <typename T>
void Stack<T>::push(const T& value) {
    list.pushForward(value);
}

template <typename T>
T Stack<T>::pop() {
    if (list.head == nullptr) {
        throw runtime_error("Stack is empty");
    }
    T popped = list.head->value;
    list.removeForward();
    return popped;
}

template <typename T>
void Stack<T>::print() const {
    for (int i = 0; i < size(); i++) {
        cout << list.get(i) << " ";
    }
}

template <typename T>
ostream& operator<<(ostream& os, const Stack<T>& stack) {
    stack.print();
    return os;
}

#endif //LR2_STACK_H
