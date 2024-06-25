///---------------------------------------------------------------------------------------------------------------------
/// Field.cpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#include "Map.hpp"
#include "Utils.hpp"
#include "Field.hpp"

#include <vector>
#include <string>

///---------------------------------------------------------------------------------------------------------------------
std::vector<int> Field::getCoordinates() 
{
  return coordinates_;
}

///---------------------------------------------------------------------------------------------------------------------
Entity* Field::getEntity() 
{
  return entity_;
}

///---------------------------------------------------------------------------------------------------------------------
void Field::setEntity(Door *door) 
{
  entity_ = door;
}

///---------------------------------------------------------------------------------------------------------------------
void Field::setEntity(Character *character) 
{
  entity_ = character;
}

///---------------------------------------------------------------------------------------------------------------------
void Field::setEntity(Chest *chest) 
{
  entity_ = chest;
}

///---------------------------------------------------------------------------------------------------------------------
void Field::setEntity(DeathLocation *death_location) 
{
  entity_ = death_location;
}

///---------------------------------------------------------------------------------------------------------------------
void Field::delEntity(void) 
{
  entity_ = nullptr;
}

///---------------------------------------------------------------------------------------------------------------------
void Field::convertCharToDL(Character* character)
{
  std::vector<Item*> loot;
  std::vector<Item*> char_weapons = character->getWeapons();
  if (character->getEquippedWeapon() != nullptr) 
  {
    char_weapons.push_back(character->getEquippedWeapon());
  }
  
  std::vector<Item*> char_armor = character->getArmor();
  if (character->getEquippedArmor() != nullptr) 
  {
    char_armor.push_back(character->getEquippedArmor()); 
  }
  std::vector<Item*> char_inventory = character->getInventory();

  loot.insert(loot.end(), char_weapons.begin(), char_weapons.end());
  loot.insert(loot.end(), char_armor.begin(), char_armor.end());
  loot.insert(loot.end(), char_inventory.begin(), char_inventory.end());

  character->clearInventory();

  DeathLocation* char_death = new DeathLocation(loot, character->getCoordinates());

  entity_ = char_death;
}

///---------------------------------------------------------------------------------------------------------------------
Field::~Field()
{
  if (entity_ != nullptr && entity_->getEntityType() != Entity::EntityType::CHARACHTER) {
    delete entity_;
  }
}
