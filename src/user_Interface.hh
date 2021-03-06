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
#ifndef USER_INTERFACE_HH
#define USER_INTERFACE_HH

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "database.hh"

#define len(x) (sizeof((x))/sizeof((x)[0]))

struct csize{
    int col;
    int rows;
};

struct credentials {
    std::string username;
    std::string password;
    std::string NamaLengkap;
    bool        admin;
};

csize getConsoleSize(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return {columns, rows};
}

void gotoxy(SHORT x, SHORT y)
{
    COORD c = { x, y };  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

bool check_slice(int input, int * array){
    while(*array != NULL){
        if(input == *array) return true;
        array++;
    }
    return false;
}

void slowprint(std::string text){
    fflush(stdout);
    for(int i=0; i<text.length(); i++){
        std::cout << text[i];
        Sleep(35);
        fflush(stdout);
    }
    fflush(stdout);
}

credentials login_screen(){
    static credentials userData[] = {
        {"wowotek", "kantongajaib", "Erlangga Ibrahim", true},
        {"aureliagbrl", "gabycantik", "Aurelia Gabriele", false},
        {"sambram", "samuelaja11", "Samuel Dwi Bramantya", false},
        {"freshman", "bimbag", "Bimo Bagus", false},
    };
    std::string username, password;

    slowprint("----- Login Screen -----\n");
    slowprint("Username : "); std::getline(std::cin, username);
    slowprint("Password : "); std::getline(std::cin, password);
    for(int i=0; i<len(userData); i++){
        if(username == userData[i].username && password == userData[i].password){
            return userData[i];
        }
    }

    slowprint("Wrong Credentials !\n"); fflush(stdout);
    Sleep(2500);
    return login_screen();
}

int main_menu(credentials user){
    if(user.admin == true){
        int input;
        int x[7] = {1, 2, 3, 4, 5, 9, NULL};
        do {
            system("cls");
            std::cout << "Welcome " << user.username << " Super User" << std::endl << std::endl;
            std::cout << "--- Admin Main Menu ---" << std::endl;
            std::cout << "1. Reservation" << std::endl;
            std::cout << "2. Check-Out" << std::endl;
            std::cout << "3. Change Guest Data" << std::endl;
            std::cout << "4. Change Room Data" << std::endl;
            std::cout << "8. Logout" << std::endl;
            std::cout << "9. Exit" << std::endl;
            std::cin >> input;
            
        } while (check_slice(input, x) !=true);
        return input;
    } else {
        int input;
        int x[5] = {1, 2, 8, 9, NULL};
        do {
            std::cout << "Welcome " << (std::string)user.username  << std::endl << std::endl;
            slowprint("--- Front-Desk Main Menu ---\n");
            std::cout << "1. Reservation" << std::endl;
            std::cout << "2. Check-Out" << std::endl;
            std::cout << "8. Logout" << std::endl;
            std::cout << "9. Exit" << std::endl;
            std::cin >> input;

        } while (check_slice(input, x)!=true);
        return input;
    }
}

void checkout_menu(RoomInterface RI){
    Room r;
    bool loop = true;
    while(loop){
        LinkedList<Room> roomData = RI.getAllRoom();
        uint32_t room_number;
        slowprint("What room you are currently in ?\n[:> ");
        std::cin >> room_number;
        for(int i=0; i<roomData.getSize(); i++){
            if(roomData[i].room_number == room_number){
                r = roomData[i];
                loop = false;
                break;
            }
        }
        slowprint("Your Room is not found ! try again !\n");
        Sleep(1500);
    }

    std::string input;
    slowprint("Are You Sure you are going to Checkout Now ?\n Y for yes, N for no : ");
    std::cin >> input;
    if(input == "Y" || input == "y"){
        r.occupied = false;
        RI.updateRoom(r.room_number, r);
    }
}

int reservation_menu(){
    int input;
    int x[4] = {1, 2, 9, NULL};
    slowprint("---- Reservation Menu ----\n");
    std::cout << "1. Room List" << std::endl;
    std::cout << "2. Reserve Room" << std::endl;
    std::cout << "9. Exit" << std::endl;
    std::cin >> input;

    if(check_slice(input, x)!=true){
        return reservation_menu();
    } else {
        return input;
    }
}

void room_list(LinkedList<Room> dbRoom){
    system("cls");
    slowprint("---- Available Room List ----\n");
    for(int i=0; i<dbRoom.getSize(); i++){
        Room d = dbRoom[i];
        if(d.occupied) continue;
        slowprint("Price Per Night : Rp "); std::cout << d.price_per_night << ",-" << std::endl;
        slowprint("    Room Number : "); std::cout << d.room_number << std::endl;
        slowprint("      Room Type : "); std::cout << d.room_type << std::endl;
        slowprint("       Bed Type : "); std::cout << d.bed_type << std::endl;
        slowprint("  Max Occupants : "); std::cout << d.max_occupants << std::endl;
        slowprint("   Smoking Room : "); std::cout << (d.smoking == true ? "yes" : "no") << std::endl;
        std::cout << std::endl;
    }
    std::string x;
    slowprint("\n\n Press Anything to Continue ...");
    std::cin >> x;
}

void reserve_room_menu(RoomInterface RI, GuestInterface GI){
    LinkedList<Room> roomData = RI.getAllRoom();
    Room r;
    uint32_t night;
    bool loop = true;
    while(loop == true){
        uint32_t room_number;
        slowprint("Enter A Room Number You want To reserve\n[:> ");
        std::cin >> room_number;
        for(int i=0; i<roomData.getSize(); i++){
            if(roomData[i].room_number == room_number){
                r = roomData[i];
                loop = false;
                break;
            }
        }
        slowprint("There is no such Room, Try Again !\n");
    }

    slowprint("How Many Night You Need to Stay ? ");
    std::cin >> night;

    Guest g;
    while(true){
        std::string name, id;
        slowprint("---- Room Reservation ----\n");
        slowprint("Please proceed to provide your identification details\n\n");
        slowprint("Identification Number : "); std::getline(std::cin, id);
        slowprint("            Full Name : "); std::getline(std::cin, name);
        std::string input;
        slowprint("Is Above details are correct ?\n Y for yes, N for no : ");
        std::cin >> input;
        if(input == "Y" || input == "y"){
            g.name = name;
            g.id = id;
            break;
        }
    }

    slowprint("Your Room Reservation is Identified By :\n    "); std::cout << g.name << std::endl;
    slowprint("Your Are Reserving\n    "); std::cout << r.room_type << std::endl;
    slowprint("A Price You Need To Pay is :");
    slowprint("    Rp "); std::cout << r.price_per_night << ",- x " << night << " = Rp ";
    std::cout << r.price_per_night * night << ",-" << std::endl;
    slowprint("Is this looks ok ?\n Y for yes, N for no");
    std::string input; std::cin >> input;
    if(input == "Y" || input == "y"){
        r.occupied = true;
        if(RI.updateRoom(r.room_number, r)==true){
            slowprint("Have a Good Night Sleep !");
        } else {
            slowprint("Sorry there is an error Occured");
        }
        return;
    } else {
        return reserve_room_menu(RI, GI);
    }
}

#endif