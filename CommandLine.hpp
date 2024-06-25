//----------------------------------------------------------------------------------------------------------------------
//
// The CommandLine class contains functionality for converting user input into a Command object.
//
// Author: Code by the Tutors of A1
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef COMMANDLINE_HPP
#define COMMANDLINE_HPP


#include <string>
#include <map>
#include <vector>
#include "Command.hpp"


class CommandLine
{

public:
  //------------------------------------------------------------------------------------------------------------------
  // Constructor and Destructor are set to default. The copy constructor is deleted explicitly.
  //
  CommandLine() = default;
  CommandLine(const CommandLine&) = delete;
  ~CommandLine() = default;

  //------------------------------------------------------------------------------------------------------------------
  // This function reads an input from the user and stores it in a Command object.
  //
  // @return the parsed Command object
  //
  Command readCommand();
  //------------------------------------------------------------------------------------------------------------------
  // This function removes leading whitespaces from a string.
  //
  // @param string - the sting to remove leading whitespaces from
  // @return void
  static void removeWhitespacesAtEnds(std::string &string);

  //------------------------------------------------------------------------------------------------------------------
  // This function splits a string into tokens using a delimiter and stores the tokens in a vector.
  //
  // @param string - the sting to split
  // @param vector - the vector to store the tokens in
  // @param delimiter -  delimiter to use for splitting
  // @return void
  static void stringToVector(const std::string &string, std::vector<std::string> &vector, char delimiter);


private:
  //------------------------------------------------------------------------------------------------------------------
  // This function removes trailing whitespaces from a string.
  //
  // @param string - the sting to remove trailing whitespaces from
  // @return void
  static void removeTrailingWhitespaces(std::string &string);

  //------------------------------------------------------------------------------------------------------------------
  // This function removes trailing and leading whitespaces from a string.
  //
  // @param string - the sting to remove whitespaces from
  // @return void
  static void removeLeadingWhitespace(std::string &string);

};


#endif //COMMANDLINE_HPP
