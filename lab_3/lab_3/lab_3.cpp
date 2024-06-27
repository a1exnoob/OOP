﻿#include <string>
#include <time.h>
#include <cstring>
#include <iostream>

template <typename T>
class Vector {

private:
    T* vec;
public:
    size_t size; // size_t - это целочисленный тип данных без знака, который может присваивать только целочисленные значения 0 и более 0.

    Vector() {
        size = 0;
        vec = new T[size];
    }

    Vector(size_t size) {
        this->size = size;
        vec = new T[size];
    }

    T operator [](size_t index) {
        if (index > size - 1) {
            return vec[size - 1];
        }
        return vec[index];
    }

    size_t size_vector() {
        return size;
    }

    void set_size(size_t size) {
        if (size == 1) {
            if (this->size != 0) {
                T tmp = vec[0];
                delete[] vec;
                vec = new T[1];
                vec[0] = tmp;
            }
            else {
                delete[] vec;
                vec = new T[1];
            }
            this->size = size;
            return;
        }
        if (size == 0) {
            delete[] vec;
            //vec == nullptr;
            this->size = size;
            return;
        }

        T* tmp = new T[size];
        for (size_t i = 0; this->size > size ? i < size : i < this->size; i++) {
            tmp[i] = vec[i];
        }
        delete[] vec;
        vec = tmp;
        this->size = size;
    }

    void push_back(T value) {
        set_size(size + 1);
        vec[size - 1] = value;
    }

    void delete_back() {
        set_size(size - 1);
    }

    void show() {
        std::cout << std::endl;
        if (size == 0) {
            std::cout << "NULL";
        }
        else {
            for (size_t i = 0; i < size; i++) {
                std::cout << vec[i];
                if (i != size - 1)
                    std::cout << ", ";
            }
        }
        std::cout << std::endl << std::endl;
    }

    ~Vector() {
        if (size != 0) delete[] vec;
    }
};


template<typename T>
class Stack {

private:
    Vector<T> vector_data;
public:
    Stack() { }

    ~Stack() { }

    void push(T data) {
        vector_data.push_back(data);
    }

    T pop() {
        T tmp = vector_data[vector_data.size - 1];
        vector_data.delete_back();
        return tmp;
    }

    size_t size() {
        return vector_data.size;
    }
};


std::string random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {

        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

int main() {

    setlocale(LC_ALL, "rus");

    Stack<std::string> strStack;
    Stack<double> DoubleStack;
    Stack<int> IntStack;
    srand(static_cast <unsigned> (time(0)));

    //STD::STRING
    for (int i = 0; i < 5; i++) {

        std::string insert(random(5));
        strStack.push(insert);
        std::cout << "Добавить в стек <std::string> : " << insert << std::endl;
    }
    std::cout << "Размер стека <std::string> : " << strStack.size() << std::endl << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << "Удалить из стека <std::string> : " << strStack.pop() << std::endl;
    }
    std::cout << "Размер стека <std::string> : " << strStack.size() << std::endl;


    std::cout << std::endl << std::endl;

    //DOUBLE
    for (int i = 0; i < 5; i++) {
        double insert = rand() * ((double)(rand()) / (double)(rand()));
        DoubleStack.push(insert);
        std::cout << "Добавить в стек <double> : " << insert << std::endl;
    }
    std::cout << "Размер стека <double> : " << DoubleStack.size() << std::endl << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << "Удалить из стека <double> : " << DoubleStack.pop() << std::endl;
    }
    std::cout << "Размер стека <double> : " << DoubleStack.size() << std::endl;


    std::cout << std::endl << std::endl;

    //INT
    for (int i = 0; i < 5; i++) {
        int insert = rand() % 100;//
        IntStack.push(insert);
        std::cout << "Добавить в стек <int> : " << insert << std::endl;
    }
    std::cout << "Размер стека <int> : " << IntStack.size() << std::endl << std::endl;

    for (int i = 0; i < 5; i++) {
        std::cout << "Удалить из стека <int> : " << IntStack.pop() << std::endl;
    }
    std::cout << "Размер стека <int> : " << IntStack.size() << std::endl;


    return 0;
}