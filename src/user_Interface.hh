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
        int x[6] = {1, 2, 3, 4, 9, NULL};
        do {
            system("cls");
            std::cout << "Welcome " << user.username << " Super User" << std::endl << std::endl;
            std::cout << "--- Admin Main Menu ---" << std::endl;
            std::cout << "1. Reservation" << std::endl;
            std::cout << "2. Check-Out" << std::endl;
            std::cout << "3. Update Guest Data" << std::endl;
            std::cout << "4. Update Room Data" << std::endl;
            std::cout << "9. Exit" << std::endl;
            std::cin >> input;
            
        } while (check_slice(input, x) !=true);
        return input;
    } else {
        int input;
        int x[4] = {1, 2, 9, NULL};
        do {
            std::cout << "Welcome " << user.username  << std::endl << std::endl;
            slowprint("--- Front-Desk Main Menu ---");
            std::cout << "1. Reservation" << std::endl;
            std::cout << "2. Check-Out" << std::endl;
            std::cout << "9. Exit" << std::endl;
            std::cin >> input;

        } while (check_slice(input, x)!=true);
        return input;
    }
}

int reservation_menu(){
    int input;
    int x[4] = {1, 2, 9, NULL};
    slowprint("---- Reservation Menu ----");
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

void room_list(){
    
}

#endif