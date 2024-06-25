///---------------------------------------------------------------------------------------------------------------------
/// Command.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <string>

class Command
{
  ///-------------------------------------------------------------------------------------------------------------------
  /// Command class
  /// Creates a command object
  ///
  public:
    ///---------------------------------------------------------------------------------------------------------------
    /// Enum for CommandType. Contains all type of commands
    ///
    enum class CommandType : char 
    {
      HELP,
      STORY,
      MAP,
      POSITIONS,
      PLAYER,
      INVENTORY,
      MOVE,
      LOOT,
      USE,
      ATTACK,
      QUIT,
      GIVE,
      INVALID,
      WRONG_PARAM
    };

    ///---------------------------------------------------------------------------------------------------------------
    /// Enum for errors. Contains all type of errrors that could occur
    ///
    enum class Errors : int 
    {
      UNKNOWN_COMMAND,
      INVALID_PARAM_COUNT,
      INVALID_PARAM,
      ENTITY_OR_ITEM_UNAVAILABLE,
      INVALID_POSITION,
      ATTACK_NO_WEAPON_EQUIPPED,
      ATTACK_NO_AMMUNITION,
      NO_ERROR
    };

  private:
    ///---------------------------------------------------------------------------------------------------------------
    /// Attributes of command object.
    /// CommandType type_ - Type of command
    /// std::vector<std::string> parameters_ - parameters for command inputed
    ///
    CommandType type_;
    std::vector<std::string> parameters_;
    int needed_params_;
  public:

  ///---------------------------------------------------------------------------------------------------------------
  /// Constructors
  ///
  Command() = default;
  Command(std::vector<std::string>& input);
  Command(CommandType type);

  ///---------------------------------------------------------------------------------------------------------------
  /// Copy constructor, set to default
  ///
  Command(const Command &Command2) = default;

  ///---------------------------------------------------------------------------------------------------------------
  /// Destructor, also set to default
  ///
  ~Command() = default;

  ///---------------------------------------------------------------------------------------------------------------
  /// Checks, if entered command is Quit
  ///
  /// @return true, if it is, false otherwise 
  ///
  bool isQuit();

  ///---------------------------------------------------------------------------------------------------------------
  /// Getter for CommandType
  ///
  /// @return type of command
  ///
  CommandType getType() const;

  ///---------------------------------------------------------------------------------------------------------------
  /// Getter for parameters
  ///
  /// @return vector of parameters
  ///
  std::vector<std::string>& getParameters();

  ///---------------------------------------------------------------------------------------------------------------
  /// Setter for command type
  ///
  /// @param type type to set
  ///
  void setType(CommandType type);

  int getNeededParams(void);
};

#endif 