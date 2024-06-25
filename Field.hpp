///---------------------------------------------------------------------------------------------------------------------
/// Field.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <string>
#include "Entity.hpp"

class Field
{
  ///-------------------------------------------------------------------------------------------------------------------
  /// Field class
  /// Represents a single unit of the room
  ///
  private:
  ///-------------------------------------------------------------------------------------------------------------------
  /// Entity* entity_ - a pointer to an Entity object, that occupies this field
  /// int row_ - first coordinate of the field
  /// int column_ - second coordinate
  /// vector<int> coordinates_ - coordinates stored as vector
  /// bool taken_ - whether it is taken or not
  ///
    Entity* entity_;
    int row_;
    int column_;
    std::vector<int> coordinates_;

  public:

  ///-------------------------------------------------------------------------------------------------------------------
  /// Constructor
  /// 
  /// @param entiry entity on the field
  /// @param row row coordinate
  /// @param column column coordinate
  ///
  Field(int row, int column) : row_(row), column_(column) 
  {
    entity_ = nullptr;
    coordinates_.resize(2);
    coordinates_[0] = row_;
    coordinates_[1] = column_;
  }

  ///-------------------------------------------------------------------------------------------------------------------
  /// Copy constructor
  ///
  Field(const Field &Field2) = delete;

  ///-------------------------------------------------------------------------------------------------------------------
  /// Destructor
  ///
  ~Field();

  ///-------------------------------------------------------------------------------------------------------------------
  /// Setters for Entity
  /// 
  /// @param entity could be a door, character or a chest
  ///
  void setEntity(Door *door);
  void setEntity(Character *character);
  void setEntity(Chest* chest);
  void setEntity(DeathLocation* death_location);

  ///---------------------------------------------------------------------------------------------------------------
  /// Getter for Entity
  ///
  Entity *getEntity();

  ///---------------------------------------------------------------------------------------------------------------
  /// Getter for Coordinates
  ///
  std::vector<int> getCoordinates();

  ///---------------------------------------------------------------------------------------------------------------
  /// Delete Entity
  ///
  void delEntity(void);

  ///---------------------------------------------------------------------------------------------------------------
  /// Death mechanic. Takes in character and converts his loot into a new death location
  ///
  void convertCharToDL(Character* character);
};

#endif // FIELD_HPP
