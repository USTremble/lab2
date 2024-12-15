#ifndef LR2_SLIST_H
#define LR2_SLIST_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
struct SNode {
    T value;
    SNode<T>* next;

    SNode(const T& val) : value(val), next(nullptr) {}
};

template <typename T>
struct SList {
    SNode<T>* head;
    int len;

    int size() const;
    void pushForward(T value);
    void pushBack(T value);
    void removeForward();
    void removeBack();
    void removeValue(const T& value);
    int findByValue(const T& value);
    string join(char delimiter);
    T get(int index) const;

    SList() : head(nullptr), len(0) {}
};

template <typename T>
int SList<T>::size() const {
    return len;
}

template <typename T>
void SList<T>::pushForward(T value) {
    SNode<T>* node = new SNode<T>(value);
    node->next = head;
    head = node;
    len++;
}

template <typename T>
void SList<T>::pushBack(T value) {
    SNode<T>* node = new SNode<T>(value);
    if (head == nullptr) {
        head = node;
    } else {
        SNode<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = node;
    }
    len++;
}

template <typename T>
void SList<T>::removeForward() {
    if (head == nullptr) {
        throw runtime_error("Nothing to remove");
    }

    SNode<T>* oldHead = head;
    head = head->next;
    delete oldHead;
    len--;
}

template <typename T>
void SList<T>::removeBack() {
    if (head == nullptr) {
        throw runtime_error("Nothing to remove");
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        SNode<T>* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    len--;
}

template <typename T>
void SList<T>::removeValue(const T& value) {
    SNode<T>* prev = nullptr;
    SNode<T>* current = head;

    while (current != nullptr) {
        if (current->value == value) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            SNode<T>* toDelete = current;
            current = current->next;
            delete toDelete;
            len--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

template <typename T>
int SList<T>::findByValue(const T& value) {
    SNode<T>* current = head;
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
string SList<T>::join(char delimiter) {
    string result;
    SNode<T>* current = head;

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
T SList<T>::get(int index) const {
    if (index < 0 || index >= len) {
        throw runtime_error("Index out of bounds");
    }

    SNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

template <typename T>
ostream& operator<<(ostream& os, const SList<T>& list) {
    SNode<T>* current = list.head;
    while (current != nullptr) {
        os << current->value << " ";
        current = current->next;
    }
    return os;
}

#endif //LR2_SLIST_H
