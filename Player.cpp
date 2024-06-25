///---------------------------------------------------------------------------------------------------------------------
/// Player.cpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#include "Player.hpp"
#include "Entity.hpp"

#include <vector>
#include <string>
#include <iostream>



///---------------------------------------------------------------------------------------------------------------------
int Player::getId() const 
{ 
  return id_;
}

///---------------------------------------------------------------------------------------------------------------------
void Player::setClass(char letter)
{
  letter = toupper(letter);
  if(letter == 'W') 
  {
    player_class_ = PlayerClass::WIZARD;
    charachter_ = new Character('W', this);
  }
  if(letter == 'B') 
  {
    player_class_ = PlayerClass::BARBARIAN;
    charachter_ = new Character('B', this);
  }
  if(letter == 'R') 
  {
    player_class_ = PlayerClass::ROGUE;
    charachter_ = new Character('R', this);
  };
}

///---------------------------------------------------------------------------------------------------------------------
Player::~Player() 
{
  delete(charachter_);
  charachter_ = nullptr;
}

///---------------------------------------------------------------------------------------------------------------------
std::string Player::getClass() const
{
  std::string playerClassStr;

  switch (player_class_)
  {
    case PlayerClass::BARBARIAN:
      playerClassStr = "Barbarian";
      break;
    case PlayerClass::WIZARD:
      playerClassStr = "Wizard";
      break;
    case PlayerClass::ROGUE:
      playerClassStr = "Rogue";
      break;
  }

  return playerClassStr;
}

///---------------------------------------------------------------------------------------------------------------------
std::string Player::getName() const 
{
  return name_;
}

///---------------------------------------------------------------------------------------------------------------------
Character *Player::getCharacter() const
{
  return charachter_;
}

///---------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Player& player) 
{
  os << player.getClass() << " [" << player.getClass()[0] << "] \"" << player.getName() << "\"";
  return os;
}
