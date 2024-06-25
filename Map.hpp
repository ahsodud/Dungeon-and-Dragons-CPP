///---------------------------------------------------------------------------------------------------------------------
/// Map.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include "Field.hpp"
#include "Player.hpp"
#include "Room.hpp"

///-------------------------------------------------------------------------------------------------------------------
/// Map class
/// Stores all rooms of dungeon as a vector
///
class Map
{
  private:
    ///---------------------------------------------------------------------------------------------------------------
    /// vector<Room> rooms_ - vector of all rooms in dungeon
    /// int total_rooms_ - number of rooms
    /// bool output_active - whether is an output active or not
    ///
    std::vector<Room *> rooms_;
    int total_rooms_;

  public:
    ///-----------------------------------------------------------------------------------------------------------------
    /// Generate map based on dungeon_config.txt
    ///
    /// @param dungeon_file dungeon file
    ///
    Map(char* dungeon_file);

    ///---------------------------------------------------------------------------------------------------------------
    /// Deleted copy constructor.
    ///
    Map(const Map &Map2) = delete;

    ///---------------------------------------------------------------------------------------------------------------
    /// Destructor set to default
    ///
    ~Map();

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for first room
    ///
    /// @return First room
    ///
    Room *getFirstRoom(void);

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for total number of rooms
    ///
    /// @return Total number of rooms
    ///
    int getTotalRooms(void);
};

#endif // MAP_HPP