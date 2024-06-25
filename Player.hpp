///---------------------------------------------------------------------------------------------------------------------
/// Player.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include "Entity.hpp"

///-------------------------------------------------------------------------------------------------------------------
/// Player class
/// Contains information about player(Character, Nickname, Class)
///
class Player
{
public:
  ///---------------------------------------------------------------------------------------------------------------
  /// enum for PlayerClass
  ///
  enum class PlayerClass : char 
  {
    WIZARD,
    ROGUE,
    BARBARIAN
  };
  
  private:
    ///---------------------------------------------------------------------------------------------------------------
    /// int id_ - ID of Player
    /// string name_ - his Nickname
    /// PlayerClass player_class_ - his class
    /// Character* character_ - a pointer to hi character_
    ///
    int id_;
    std::string name_;
    PlayerClass player_class_;
    Character* charachter_;

  public:
    ///---------------------------------------------------------------------------------------------------------------
    /// Constructor. Creates a player with ID and name
    ///
    Player(std::string name, int id): id_(id),name_(name){}

    ///---------------------------------------------------------------------------------------------------------------
    /// Copy constructor deleted
    ///
    Player(const Player&) = delete;

    ///---------------------------------------------------------------------------------------------------------------
    ///Destructor
    ///
    ~Player();
    
    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for players ID
    ///
    /// @return players ID
    ///
    int getId() const;

    ///---------------------------------------------------------------------------------------------------------------
    /// Setter for players class
    ///
    void setClass(char letter);

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for players class
    ///
    /// @return players class
    ///
    std::string getClass() const;

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for players nickname
    ///
    /// @return players nickname
    ///
    std::string getName() const;

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for players character
    ///
    /// @return players character
    ///
    Character *getCharacter() const;

    ///---------------------------------------------------------------------------------------------------------------
    /// Overloaded operator for better output
    ///
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif