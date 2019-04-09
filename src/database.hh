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

struct Guest {
    std::string id;             // Primary Key or Unique ID
    std::string name;
};

struct Room{
    int room_number;            // Primary Key or Unique ID
    std::string room_type;
    int max_occupants;          // Maximum Occupants per Room
    bool key_on_guest;
};

struct guest_node_t {
    Guest guest_data;
    guest_node_t * next_data;
};

struct room_node_t {
    Room room_data;
    room_node_t * next_data;
};

#endif