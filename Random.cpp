///---------------------------------------------------------------------------------------------------------------------
/// Random.cpp
///
/// Authors: Tutors
///---------------------------------------------------------------------------------------------------------------------

#include "Random.hpp"

#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

using Oop::Random;

///---------------------------------------------------------------------------------------------------------------------
std::string const Random::SEED{"RAND_SEED"};

///---------------------------------------------------------------------------------------------------------------------
Random::Random() : mersenne_twister_(getSeed(SEED))
{
}

///---------------------------------------------------------------------------------------------------------------------
Random& Random::getInstance()
{
  static Random instance{};
  return instance;
}

///---------------------------------------------------------------------------------------------------------------------
size_t Random::getRandomNumber(size_t const upper_bound)
{
  std::uniform_int_distribution<size_t> normal_distribution{1, upper_bound};
  return normal_distribution(mersenne_twister_);
}

///---------------------------------------------------------------------------------------------------------------------
size_t Random::getSeed(std::string const environment_variable)
{
  size_t seed{};

  try
  {
    seed = getEnvironmentSeed(environment_variable);
  }
  catch (std::runtime_error& exception)
  {
    seed = getHardwareSeed();
  }

  return seed;
}

///---------------------------------------------------------------------------------------------------------------------
size_t Random::getEnvironmentSeed(std::string const environment_variable)
{
  char* environment_seed{getenv(environment_variable.c_str())};

  if (environment_seed)
  {
    return parseSeed(environment_seed);
  }

  throw  std::runtime_error{"Environment variable \"" + environment_variable + "\" does not exist."};
}

///---------------------------------------------------------------------------------------------------------------------
size_t Random::getHardwareSeed()
{
  std::random_device seed_from_hardware{};
  return seed_from_hardware();
}

///---------------------------------------------------------------------------------------------------------------------
size_t Random::parseSeed(std::string const seed)
{
  std::stringstream seed_stream{seed};
  size_t seed_value{};

  seed_stream >> seed_value;

  if (seed_stream.eof() && !seed_stream.bad())
  {
    return seed_value;
  }

  throw  std::runtime_error{"Could not parse the seed \"" + seed + "\"."};
}

