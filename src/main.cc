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

#include <iostream>
#include "user_Interface.hh"

int main(){
    while(true){
        RoomInterface RI;
        GuestInterface GI;
        credentials loginCredential = login_screen();
        if(loginCredential.admin == true){
            switch(main_menu(loginCredential)){
                default: break;
                case 9: return 0;
                case 1:
                    reservation_menu();
                    break;
                case 2:
                    checkout_menu(RI);
                    break;
                case 3:
                    std::cout << "Not Implemented Yet !" << std::endl; Sleep(1500);
                    break;
                case 4:
                    std::cout << "Not Implemented Yet !" << std::endl; Sleep(1500);
                    break;
            }
        } else {
            switch(main_menu(loginCredential)){
                default: break;
                case 9: return 0;
                case 1:
                    reservation_menu();
                    break;
                case 2:
                    checkout_menu(RI);
                    break;
            }
        }
    }
    return 1;
}