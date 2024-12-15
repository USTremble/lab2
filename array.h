#ifndef LR2_ARRAY_H
#define LR2_ARRAY_H

#include <iostream>
using namespace std;

template <typename T>
struct Array {
    T* data;
    int len; // текущие
    int cap; // емкость

    Array(int initCap = 16) {
        cap = initCap;
        len = 0;
        data = new T[cap];
    }

    int size();
    void extend();
    void pushBack(T);
    void insert(int, T);
    void remove(int);
    void set(int, T);
    void reverse();
    T get(int index);
};

template <typename T>
int Array<T>::size() {
    return len;
}

template <typename T>
void Array<T>::extend() {
    int newCap = cap * 2;
    T* newData = new T[newCap];
    for (int i = 0; i < cap; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    cap = newCap;
}

template <typename T>
void Array<T>::pushBack(T value) {
    if (static_cast<float>(len) / cap >= 0.5) { // если заполнен >= 50% - увеличиваем объём
        extend();
    }
    data[len] = value;
    len++;
}

template <typename T>
void Array<T>::insert(int index, T value) {
    if (static_cast<float>(len) / cap >= 0.5) {
        extend();
    }
    for (int i = len; i > index; i--) {
        data[i] = data[i - 1];  // двигаем элементы с конца на лево
    }
    data[index] = value;
    len++;
}

template <typename T>
void Array<T>::remove(int index) {
    if (index < 0 || index >= len) {
        throw invalid_argument("Invalid index");
    }
    for (int i = index; i < len - 1; i++) {
        data[i] = data[i + 1]; // двигаем вперед
    }
    len--;
}

template <typename T>
void Array<T>::set(int index, T value) {
    if (index < 0 || index >= len) {
        throw invalid_argument("Invalid index");
    }
    data[index] = value;
}

template <typename T>
void Array<T>::reverse() {
    for (int i = 0; i < len / 2; i++) {
        T temp = data[i];
        data[i] = data[len - i - 1];
        data[len - i - 1] = temp;
    }
}

template <typename T>
T Array<T>::get(int index) {
    if (index < 0 || index >= len) {
        throw invalid_argument("Invalid index");
    }

    return data[index];
}

template <typename T>
ostream& operator<<(ostream& os, Array<T>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        os << arr.get(i);
        if (i != arr.size() - 1) {
            os << ',';
        }
    }
    os << endl;
    return os;
}

#endif //LR2_ARRAY_H
