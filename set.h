#ifndef LR2_SET_H
#define LR2_SET_H

#include <string>
#include <iostream>
#include "array.h"
#include "slist.h"

using namespace std;

template <typename T>
struct Set {
    SList<T> data;

    int contains(T value);
    int size() const;
    void add(T value);
    void remove(T value);
    Array<T> values() ;
    void print() const;

    Set() {}
};

template <typename T>
int Set<T>::size() const{
    return data.size();
}

template <typename T>
int Set<T>::contains(T value) {
    return data.findByValue(value);
}

template <typename T>
void Set<T>::remove(T value) {
    data.removeValue(value);
}

template <typename T>
void Set<T>::add(T value) {
    if (contains(value) == -1) {
        data.pushBack(value);
    }
}

template <typename T>
Array<T> Set<T>::values() {
    Array<T> result;

    for (int i = 0; i < data.size(); i++) {
        result.pushBack(data.get(i));
    }

    return result;
}

template <typename T>
void Set<T>::print() const {
    for (int i = 0; i < data.size(); i++) {
        cout << data.get(i) << " ";
    }
}

template <typename T>
ostream& operator<<(ostream& os, const Set<T>& set) {
    set.print();
    return os;
}

#endif //LR2_SET_H
