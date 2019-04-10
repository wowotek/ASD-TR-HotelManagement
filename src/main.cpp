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
    RoomInterface RI;
    GuestInterface GI;
    Room rx1, rx2, rx3;
    rx1.room_number = 101;
    rx1.room_type = "Superior";
    rx1.bed_type = "Twin Bed";
    rx1.price_per_night = 125000;
    rx1.max_occupants = 2;
    rx1.smoking = false;
    rx1.occupied = false;

    RI.addRoom(rx1);

    rx2.room_number = 202;
    rx2.room_type = "Deluxe";
    rx2.bed_type = "King Size";
    rx2.price_per_night = 345000;
    rx2.max_occupants = 3;
    rx2.smoking = false;
    rx2.occupied = false;
    
    RI.addRoom(rx2);

    rx3.room_number = 303;
    rx3.room_type = "Suite";
    rx3.bed_type = "King Size";
    rx3.price_per_night = 780000;
    rx3.max_occupants = 3;
    rx3.smoking = true;
    rx3.occupied = false;
    
    RI.addRoom(rx3);

    credentials loginCredential = login_screen();
    while(true){
        if(loginCredential.admin == true){
            switch(main_menu(loginCredential)){
                default: break;
                case 8: return main();
                case 9: return 0;
                case 1:
                    switch(reservation_menu()){
                        case 1:
                            room_list(RI.getAllRoom());
                            break;
                        case 2:
                            reserve_room_menu(RI, GI);
                    }
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
        }
    }
}