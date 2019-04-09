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

#include <iostream>
#include <string>

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

class GuestInterface{
    private:
        LinkedList<Guest> dbGuest;
    public:
        void addGuest(Guest newGuestData){
            dbGuest.push(newGuestData);
        }

        LinkedList<Guest> getAllGuestData(){
            return dbGuest;
        }

        Guest getGuest(std::string);
        bool updateGuest(std::string, Guest);
        bool deleteGuest(std::string);
};

Guest GuestInterface::getGuest(std::string guestId){
    for(int i=0; i<dbGuest.getSize(); i++){
        if(dbGuest[i].id == guestId){
            return dbGuest[i];
        }
    } 
    std::cout << "Guest Not Found !" << std::endl;
    return;
}
bool GuestInterface::updateGuest(std::string guestId, Guest updated_data){
    for(int i=0; i<dbGuest.getSize(); i++){
        if(dbGuest[i].id == guestId){
            dbGuest[i].name = updated_data.name;
            dbGuest[i].id = updated_data.id;
            return true;
        }
    } 
    return false;
}
bool GuestInterface::deleteGuest(std::string guestId){
    LinkedList<Guest> newDb;
    for(int i=0; i<dbGuest.getSize(); i++){
        if(dbGuest[i].id == guestId){
            continue;
        }
        Guest x;
        x.name = dbGuest[i].name;
        x.id = dbGuest[i].id;
        newDb.push(x);
    }
    dbGuest = newDb;
    return true;
}

class RoomInterface{
    private:
        LinkedList<Room> dbRoom;
    public:
        void addRoom(Room room){
            dbRoom.push(room);
        }
        LinkedList<Room> getAllRoom(){
            return dbRoom;
        }
        Room getRoom(uint32_t);
        bool updateRoom(uint32_t, Room);
        bool deleteRoom(uint32_t);
};

Room RoomInterface::getRoom(uint32_t roomNumber){
    for(int i=0; i<dbRoom.getSize(); i++){
        if(dbRoom[i].room_number == roomNumber){
            return dbRoom[i];
        }
    }
    return;
}

bool RoomInterface::updateRoom(uint32_t roomNumber, Room newRoom){
    for(int i=0; i<dbRoom.getSize(); i++){
        if(dbRoom[i].room_number == roomNumber){
            dbRoom[i].room_number = newRoom.room_number;
            dbRoom[i].room_type = newRoom.room_type;
            dbRoom[i].bed_type = newRoom.bed_type;
            dbRoom[i].smoking = newRoom.smoking;

            return true;
        }
    }
    return false;
}

bool RoomInterface::deleteRoom(uint32_t roomNumber){
    LinkedList<Room> newDb;
    for(int i=0; i<dbRoom.getSize(); i++){
        if(dbRoom[i].room_number == roomNumber){
            continue;
        }
        newDb.push(dbRoom[i]);
    }
    dbRoom = newDb;
    return true;
}

#endif