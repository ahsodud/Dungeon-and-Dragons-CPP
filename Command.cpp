///---------------------------------------------------------------------------------------------------------------------
/// Random.hpp
///
/// Authors: Group-015(Partially copied from A1)
///---------------------------------------------------------------------------------------------------------------------

#include "Command.hpp"

#include <vector>
#include <string>
#include <cctype>
#include <iostream>

//---------------------------------------------------------------------------------------------------------------------
///
/// Constructor for command object
///
/// @param vector a vector, that stores a command as a string at 0 position, and parameters for it on positions further(also strings)
///
/// @return assighned CommandType and vector of parameters_
//
Command::Command(std::vector<std::string>& input)
{
  if (input[0] == "QUIT" || input.empty()) 
  {
    type_ = CommandType::QUIT;
    needed_params_ = 0;
  }
  else if (input[0] == "HELP") 
  {
    type_ = CommandType::HELP;
    needed_params_ = 0;
  }
  else if (input[0] == "STORY") 
  {
    type_ = CommandType::STORY;
    needed_params_ = 0;
  }
  else if (input[0] == "MAP") 
  {
    type_ = CommandType::MAP;
    needed_params_ = 0;
  }
  else if (input[0] == "POSITIONS") 
  {
    type_ = CommandType::POSITIONS;
    needed_params_ = 0;
  }
  else if (input[0] == "PLAYER") 
  {
    type_ = CommandType::PLAYER;
    needed_params_ = 1;
  }
  else if (input[0] == "INVENTORY") 
  {
    type_ = CommandType::INVENTORY;
    needed_params_ = 1;
  }
  else if (input[0] == "MOVE") 
  {
    type_ = CommandType::MOVE;
    needed_params_ = 2;
  }
  else if (input[0] == "LOOT") 
  {
    type_ = CommandType::LOOT;
    needed_params_ = 2;
  }
  else if (input[0] == "USE") 
  {
    type_ = CommandType::USE;
    needed_params_ = 2;
  }
  else if (input[0] == "ATTACK") 
  {
    type_ = CommandType::ATTACK;
    needed_params_ = 2;
  }
  else if (input[0] == "GIVE") 
  {
    type_ = CommandType::GIVE;
    needed_params_ = 3;
  }
  else 
  {
    type_ = CommandType::INVALID;
    return;
  }

  input.erase(input.begin());
  parameters_ = input;
};

///---------------------------------------------------------------------------------------------------------------------
Command::Command(CommandType type)
{
  type_ = type;
};

///---------------------------------------------------------------------------------------------------------------------
bool Command::isQuit() 
{
  if (type_ == CommandType::QUIT)
  {
    return true;
  }
  return false;
};

///---------------------------------------------------------------------------------------------------------------------
Command::CommandType Command::getType() const 
{
  return type_;
};

///---------------------------------------------------------------------------------------------------------------------
std::vector<std::string>& Command::getParameters()
{
  return parameters_;
};

///---------------------------------------------------------------------------------------------------------------------
void Command::setType(Command::CommandType type) 
{
  type_ = type;
};

///---------------------------------------------------------------------------------------------------------------------
int Command::getNeededParams(void) 
{
  return needed_params_;
}