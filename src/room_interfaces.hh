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
#ifndef INCLUDE_ROOM_INTERFACE_HH
#define INCLUDE_ROOM_INTERFACE_HH

#include "database.hh"

class RoomInterface {
    public:
        bool add_room(Room room);
        Room get_room(std::string room_number);
        Room * get_all_room();
        Room * get_unoccupied_room();
        bool update_room(std::string id, Room new_data);
        bool delete_guest(std::string id);
    private:
        Room room_database = NULL;
};

#endif