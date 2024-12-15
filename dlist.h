#ifndef LR2_DLIST_H
#define LR2_DLIST_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct DNode {
    T value;
    DNode<T>* next;
    DNode<T>* prev;

    DNode(const T& val) : value(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
struct Dlist {
    DNode<T>* head;
    DNode<T>* tail;
    int len;

    int size() const;
    T get(int index) const;
    void pushForward(T value);
    void pushBack(T value);
    void removeForward();
    void removeBack();
    void removeValue(const T& value);
    int findByValue(const T& value);
    string join(char delimiter);

    Dlist() : head(nullptr), tail(nullptr), len(0) {}
};

template <typename T>
int Dlist<T>::size() const {
    return len;
}

template <typename T>
T Dlist<T>::get(int index) const {
    if (index < 0 || index >= len) {
        throw runtime_error("Index out of bounds");
    }

    DNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T>
void Dlist<T>::pushForward(T value) {
    DNode<T>* node = new DNode<T>(value);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        DNode<T>* oldHead = head;
        head = node;
        node->next = oldHead;
        oldHead->prev = node;
    }
    len++;
}

template <typename T>
void Dlist<T>::pushBack(T value) {
    DNode<T>* node = new DNode<T>(value);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    len++;
}

template <typename T>
void Dlist<T>::removeForward() {
    if (head == nullptr) {
        throw runtime_error("Nothing to remove");
    }

    DNode<T>* oldHead = head;
    head = head->next; // сдвигаем на следующий узел
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete oldHead;
    len--;
}

template <typename T>
void Dlist<T>::removeBack() {
    if (head == nullptr) {
        throw runtime_error("Nothing to remove");
    }

    if (head->next == nullptr) { // если 1ый элемент
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        DNode<T>* current = tail;
        current->prev->next = nullptr; // предыдущий указывает на ничто
        tail = current->prev;
        delete current;
    }
    len--;
}

template <typename T>
void Dlist<T>::removeValue(const T& value) {
    DNode<T>* current = head;

    while (current != nullptr) {
        if (current->value == value) { // если встретили
            DNode<T>* toDelete = current;
            if (current->prev != nullptr) {  // у текущего есть предыдущий
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != nullptr) { // есть следующий
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            current = current->next;
            delete toDelete;
            len--;
        } else {
            current = current->next;
        }
    }
}

template <typename T>
int Dlist<T>::findByValue(const T& value) {
    DNode<T>* current = head;
    int index = 0;
    while (current != nullptr) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
string Dlist<T>::join(char delimiter) {
    string result;
    DNode<T>* current = head;

    while (current != nullptr) {
        result += current->value;
        if (current->next != nullptr) {
            result += delimiter;
        }
        current = current->next;
    }

    return result;
}

template <typename T>
ostream& operator<<(ostream& os, const Dlist<T>& list) {
    DNode<T>* current = list.head;
    while (current != nullptr) {
        os << current->value << " ";
        current = current->next;
    }
    return os;
}

#endif //LR2_DLIST_H
