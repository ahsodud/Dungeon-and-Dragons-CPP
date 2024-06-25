//----------------------------------------------------------------------------------------------------------------------
//
// The CommandLine class contains functionality for converting user input into a Command object.
//
// Author: Code by the Tutors of A1
//---------------------------------------------------------------------------------------------------------------------
//

#include <iostream>
#include "Command.hpp"
#include "CommandLine.hpp"


void CommandLine::removeTrailingWhitespaces(std::string &string)
{
  size_t end = string.find_last_not_of(' ');
  string = end == std::string::npos ? "" : string.substr(0, end + 1);
}

void CommandLine::removeLeadingWhitespace(std::string &string)
{
  auto start = string.find_first_not_of(' ');
  string = start == std::string::npos ? "" : string.substr(start);
}

void CommandLine::removeWhitespacesAtEnds(std::string &string)
{
  removeLeadingWhitespace(string);
  removeTrailingWhitespaces(string);
}

void CommandLine::stringToVector(const std::string &string, std::vector<std::string> &vector, char delimiter)
{
  size_t position = 0;
  size_t position2;
  std::string split_word;
  while ((position2 = string.find(delimiter, position)) != std::string::npos)
  {
    split_word = string.substr(position, position2 - position);
    position = position2 + 1;
    removeWhitespacesAtEnds(split_word);
    if (!split_word.empty())
    {
      vector.push_back(split_word);
    }
  }
  vector.push_back(string.substr(position));
}



Command CommandLine::readCommand()
{
  std::cout << "> ";
  std::string input;
  std::getline(std::cin, input);
  removeWhitespacesAtEnds(input);
  if (input.empty())
  {
    return Command(Command::CommandType::QUIT);
  }
  std::vector<std::string> vectorised_string;
  stringToVector(input, vectorised_string, ' ');
  
  for (auto &input_string : vectorised_string) {
    for (char &c : input_string) {
      c = toupper(c);
    }
  }

  Command command(vectorised_string);
  command.getType();
  /*
  switch (command.getType())
  {
    case Command::CommandType::QUIT:
      if (!command.getParameters().empty())
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::HELP:
      if (!command.getParameters().empty())
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::STORY:
      if (!command.getParameters().empty())
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::MAP:
      if (!command.getParameters().empty())
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::POSITIONS:
      if (!command.getParameters().empty())
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::PLAYER:
      if (command.getParameters().size() != 1)
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::INVENTORY:
      if (command.getParameters().size() != 1)
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::MOVE:
      if (command.getParameters().size() != 2)
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::LOOT:
      if (command.getParameters().size() != 2)
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::USE:
      if (command.getParameters().size() != 2)
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::ATTACK:
      if (command.getParameters().size() != 2)
      {
        command.setType(Command::CommandType::WRONG_PARAM);
      }
      break;
    case Command::CommandType::WRONG_PARAM:
      break;
    case Command::CommandType::INVALID:
      std::cout << "!! Invalid COMMAND." << std::endl;
      return command;
  }
  if (command.getType() == Command::CommandType::WRONG_PARAM)
  {
    std::cout << "!! Invalid AMOUNT OF PARAMETERS." << std::endl;
  } */
  return command;
}
