///---------------------------------------------------------------------------------------------------------------------
/// Map.cpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#include "Map.hpp"
#include "Field.hpp"
#include "Player.hpp"
#include "Utils.hpp"

#include <iostream>
#include <vector>
#include <string>

///---------------------------------------------------------------------------------------------------------------------
Map::Map(char* dungeon_file)
{
  std::ifstream config(dungeon_file);

  config.ignore(8, '\n');
  int total_rooms = 0;

  Room *new_room;
  std::vector<std::string> rows = Utils::readRows(config);

  for (auto room_params : rows) 
  {
    new_room = new Room(room_params);
    rooms_.push_back(new_room);
    total_rooms++;
  }

  total_rooms_ = total_rooms;
  config.close();

  for (auto& room : rooms_) 
  {
    room->initDoorPointers(rooms_);
  }
}

///---------------------------------------------------------------------------------------------------------------------
Map::~Map() 
{
  for (Room *room : rooms_) 
  {
    delete room;
  }
  rooms_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
Room *Map::getFirstRoom(void) 
{
  return rooms_[0];
}

///---------------------------------------------------------------------------------------------------------------------
int Map::getTotalRooms(void) 
{
  return total_rooms_;
}
