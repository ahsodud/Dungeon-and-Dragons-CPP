//---------------------------------------------------------------------------------------------------------------------
//
// The Utils class contains some useful functions for use in other classes.
//
// Author: Tutors
//---------------------------------------------------------------------------------------------------------------------
//

#include "Utils.hpp"

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

///------------------------------------------------------------------------------------------------------------------
bool Utils::decimalStringToInt(const std::string& str, int& number)
{
  size_t position = 0;

  try
  {
    number = std::stoul(str, &position, 10);
  }
  catch (std::invalid_argument &e)
  {
    return false;
  }
  catch (std::out_of_range &e)
  {
    return false;
  }

  return position == str.length();
};

///------------------------------------------------------------------------------------------------------------------
std::vector<std::string> Utils::readRows(std::ifstream& file) 
{
  std::vector<string> rows;
  std::string line;

  while (std::getline(file, line)) 
  {
    rows.push_back(line);
  }

  return rows;
};
