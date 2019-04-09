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
#ifndef INCLUDE_INTERFACE_HH
#define INCLUDE_INTERFACE_HH

#include "database.hh"

class GuestInterface {
    public:
        GuestInterface();
        ~GuestInterface();
        bool add_guest(Guest guest);
        Guest get_guest(std::string id);
        Guest * get_all_guest();
        bool update_guest(std::string id, Guest new_data);
        bool delete_guest(std::string id);
    private:
        guest_node_t * guest_database;
        guest_node_t * last_node(guest_node_t* x) {
            while (x->next_data != NULL) x = x->next_data;
            return x;
        }
 
        guest_node_t * push_node(guest_node_t * x, const guest_node_t * next){
            if (x != NULL) {
                x = last_node(x)->next_data;
                x = (guest_node_t*)(calloc(1, sizeof(guest_node_t)));
                memcpy(&x->guest_data, &next->guest_data, sizeof(next->guest_data));
            } else {
                x = (guest_node_t*)(calloc(1, sizeof(guest_node_t)));
                memcpy(&x->guest_data, &next->guest_data, sizeof(next->guest_data));
            }

            return x;
        }
};

GuestInterface::GuestInterface(){
    //guest_database = (guest_node_t *)(malloc(sizeof(guest_node_t)));
    guest_database = (guest_node_t *)(calloc(1, sizeof(guest_node_t)));
}

bool GuestInterface::add_guest(Guest new_guest){
    if (this != NULL){

    }
}


#endif