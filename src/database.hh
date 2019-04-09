/* 
 * <main.cc> a main routine of the entire project
 * Copyright (C) 2019 Erlangga Ibrahim, Bimo Bagus
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef INCLUDE_DATABASE_HH
#define INCLUDE_DATABASE_HH

#include <string>
#include <iostream>

template<typename T> struct Node {
    Node<T> *next;
    T head;
    public:

    Node<T>(void);
    Node<T>(const T&);

    template<typename> friend struct LinkedList;
};

template<typename T> Node<T>::Node(void): next(nullptr), head() {}
template<typename T> Node<T>::Node(const T& _) { this->head = _; }


template<typename T> struct LinkedList {
    Node<T> *root;
    size_t size;
    public:

    LinkedList(void);
    ~LinkedList(void);

    void push(const T&);
    void pop(void);
    size_t getSize(void) const;

    T& operator[] (int);
};

template<typename T> LinkedList<T>::LinkedList(void): root(nullptr), size(0) {}

template<typename T>
void LinkedList<T>::push(const T& _) {

    if (this->root == nullptr)
    {
        this->root = new Node<T>(_);
    }
    else
    {
        Node<T>* node = this->root;
        while ((node = node->next) != nullptr);
        node = new Node<T>(_);
    }

    ++this->size;
}

template<typename T>
void LinkedList<T>::pop(void) {
    Node<T> *node = this->root;

    for(size_t i = 0; i < this->size-1; ++i) node = node->next;

    delete node->next;
    node->next = nullptr;
    
    --this->size;
}

template<typename T> size_t LinkedList<T>::getSize(void) const { return this->size; }


template<typename T>
T& LinkedList<T>::operator[] (int index) {
    if(index < this->size - 1 && index >= 0) {
        Node<T> *node = this->root;

        for(size_t i = 0; i < index && node != nullptr; ++i) node = node->next;

        return node->head;    
    } else {
        throw std::runtime_error("node is nullptr!");
    }
}

struct Guest {
    std::string id;                 // Unique ID
    std::string name;
};

struct Room {
    uint32_t room_number;           // Unique ID
    std::string room_type;
    std::string bed_type;
    uint32_t price_per_night;
    bool smoking;
};

#endif