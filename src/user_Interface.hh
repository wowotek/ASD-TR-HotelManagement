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

struct csize{
    int col;
    int rows;
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
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void slowprint(std::string text){
    for(int i=0; i<text.length(); i++){
        std::cout << text[i];
        Sleep(35);
        fflush(stdout);
    }
}

void login_screen(){
    gotoxy(2, 2);
    
}

#endif