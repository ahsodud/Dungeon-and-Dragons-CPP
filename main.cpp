//----------------------------------------------------------------------------------------------------------------------
// main.cpp
//
// Author: Code by the Tutors of A1
//----------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "Game.hpp"
#include "CommandLine.hpp"
#include "Command.hpp"

enum ReturnValues
{
  SUCCESSFUL = 0,
  NOT_ENOUGH_MEMORY = 1,
  WRONG_NUMBER_OF_PARAMETERS = 2,
  INVALID_FILE = 3,
};

//----------------------------------------------------------------------------------------------------------------------
// The main program. Controls the application on a high level view.
// Creates the game and a command line interface, handles the user input and execution of commands.
//
//
// @param argc, argument count, has to be exactly 2
// @param argv, argument vector, contains the name of the csv-file
// @return 0 (SUCCESSFUL), if the application was closed without errors
//         a non-zero number is returned in the case of failure
//
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cout << "Error: Wrong number of parameters!" << std::endl;
    return WRONG_NUMBER_OF_PARAMETERS;
  }

  if (!Game::isValidConfigDungeon(argv[1]))
  {
    std::cout << "Error: Invalid file (" << argv[1] << ")!" << std::endl;
    return INVALID_FILE;
  }

  if (!Game::isValidConfigStory(argv[2]))
  {
    std::cout << "Error: Invalid file (" << argv[2] << ")!" << std::endl;
    return INVALID_FILE;
  }
  
  Game game(argv[1], argv[2]);
  
  if(game.start())
  {
    return SUCCESSFUL;
  }

  CommandLine cli;

  while (game.isRunning())
  {
    Command command = cli.readCommand();
    if (command.isQuit())
      break;
    try
    {
    game.execute(command);
    }
    catch (const std::bad_alloc& e)
    {
      return NOT_ENOUGH_MEMORY;
    }
  }

  return SUCCESSFUL;
}

