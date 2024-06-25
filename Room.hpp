///---------------------------------------------------------------------------------------------------------------------
/// Room.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Character;
class Field;
class Player;


///-------------------------------------------------------------------------------------------------------------------
/// Room class
/// Stores all fields of a dungeon room as a vector
///
class Room
{
  private:
    ///---------------------------------------------------------------------------------------------------------------
    /// int columns_ - number of columns
    /// int rows_ - number of rows_
    /// int id_ - ID of room
    /// bool entered_first_ - whether was it first entered(for messange output)
    /// vector<Character*> - all enemies inside this room
    /// vector<vector<Field*>> - all fields stored as 2D vector
    ///
    int columns_;
    int rows_;
    int id_;
    bool entered_first_;
    std::vector<Character *> enemies_;
    int alive_enemies_;
    std::vector<std::vector<Field*>> fields_;

  public:

    ///---------------------------------------------------------------------------------------------------------------
    /// Constructor. Takes in vector of rooms from map constructor
    ///
    /// @param room_params Parameters of room
    /// @param rooms vector of rooms, parced from map constructor
    ///
    ///
    Room(std::string& room_params);

    ///---------------------------------------------------------------------------------------------------------------
    /// Copy constructor set to default
    ///
    Room(const Room &Room2) = default;

    ///---------------------------------------------------------------------------------------------------------------
    /// Destructor set to default
    ///
    ~Room();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for rooms ID
    ///
    /// @return rooms ID
    ///
    int getId(void);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for rooms columns number
    ///
    /// @return number of columns
    ///
    int getColumns();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for rooms rows number
    ///
    /// @return number of rows
    ///
    int getRows();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for signs of enemies in room
    ///
    /// @return signs of enemies
    ///
    std::string getEnemiesSigns(void);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for fields in this room
    ///
    /// @return vector of fields
    ///
    std::vector<std::vector<Field*>>& getFields();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for enemies in this room
    ///
    /// @return vector of enemies
    ///
    std::vector<Character *> getEnemies();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for entered first
    ///
    /// @return true, if entered first, false otherwise
    ///
    bool enteredFirst(void);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Print map method
    ///
    void printMap(void);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Print enemies signs under map
    ///
    void printEnemies(void);
    
    ///-----------------------------------------------------------------------------------------------------------------
    /// Method that finds room base
    ///
    /// @param room_id which romm to find
    /// @param vectorRoom where to find
    ///
    /// @return desired room
    ///
    static Room *findRoom(int room_id, std::vector<Room *> rooms);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Method to find empty spot clockwise
    ///
    /// @return coordinates of empty spot
    ///
    std::vector<int> findEmptySpot(int start_row, int start_column);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Deactivates messange output for rooms, that was already entered
    ///
    void SwitchEnteredFirst();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Logic for enemy phase
    ///
    /// @param vector of players
    ///
    void enemyPhase(std::vector<Player *> players_);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Possible fields
    ///
    /// @return number of possible fields
    ///
    int countPossibleFields(std::vector<int> position);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Identify random positions
    ///
    /// @param vector of coordinates
    ///
    std::vector<int> identifyRandomPosition(int random_number, std::vector<int> position);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Function to sort enemies alphabetically
    ///
    /// @param vector of sorted enemies
    ///
    std::vector<Character *> sortEnemies();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Used to set number of alive enemies
    ///
    /// @param count desired number of enemies
    ///
    void setAliveEnemies(int count);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Initializing door by using dynamic cast on entity object
    ///
    /// @param vector Room*
    ///
    void initDoorPointers(std::vector<Room *> rooms);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Destructor for all charachters on the map
    ///
    void resetCharacters();
};


#endif
