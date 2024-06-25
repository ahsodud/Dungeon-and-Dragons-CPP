///---------------------------------------------------------------------------------------------------------------------
/// Item.cpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#include "Item.hpp"
#include "Random.hpp"
#include "Entity.hpp"
#include "Field.hpp"
#include "Game.hpp"

#include <vector>
#include <string>
#include <algorithm>

///---------------------------------------------------------------------------------------------------------------------
Item::Item(std::string item, int amount) 
{
  amount_ = amount;
  abbreviation_ = item;
}

///---------------------------------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Item& item) 
{
  os << "[" << item.getAbbreviation() << "] " << item.getName() << " (" << item.getAmount() << ")";
  return os;
}

///---------------------------------------------------------------------------------------------------------------------
HealthPotions::HealthPotions(std::string item, int amount) 
{
  amount_ = amount;
  abbreviation_ = item;
  type_ = ItemType::CONSUMABLES;


  if (item == "NHEP") 
  {
    full_name_ = "Normal Health Potion";
    dice_amount_ = 2;
  } 
  else if (item == "GHEP") 
  {
    full_name_ = "Greater Health Potion";
    dice_amount_ = 4;
  } 
  else if (item == "SHEP") 
  {
    full_name_ = "Superior Health Potion";
    dice_amount_ = 8;
  } 

  type_ = ItemType::CONSUMABLES;
}

///---------------------------------------------------------------------------------------------------------------------
ResistPotions::ResistPotions(std::string item, int amount) 
{
  amount_ = amount;
  abbreviation_ = item;
  type_ = ItemType::CONSUMABLES;


  if (item == "FIRS") 
  {
    full_name_ = "Potion of Fire Resistance";
    resist_type_ = Item::DamageType::FIRE;
  } 
  else if (item == "CORS") 
  {
    full_name_ = "Potion of Cold Resistance";
    resist_type_ = Item::DamageType::COLD;
  } 
  else if (item == "FORS") 
  {
    full_name_ = "Potion of Force Resistance";
    resist_type_ = Item::DamageType::FORCE;
  } 
  else if (item == "ACRS") 
  {
    full_name_ = "Potion of Acid Resistance";
    resist_type_ = Item::DamageType::ACID;
  } 
}

///---------------------------------------------------------------------------------------------------------------------
Ammunition::Ammunition(std::string item, int amount) 
{
  amount_ = amount;
  abbreviation_ = item;
  type_ = ItemType::CONSUMABLES;


  if (item == "ARRW") 
  {
      full_name_ = "Arrow";
  } 
  else if (item == "BOLT") 
  {
      full_name_ = "Bolt";
  }
}

///---------------------------------------------------------------------------------------------------------------------
Armor::Armor(std::string item, int amount) 
{
  amount_ = amount;
  abbreviation_ = item;
  type_ = ItemType::ARMOR;


  if (item == "LARM") 
  {
    full_name_ = "Leather Armor";
    armor_value_ = 1;
  } 
  else if (item == "BPLT") 
  {
    full_name_ = "Breastplate";
    armor_value_ = 4;
  } 
  else if (item == "CHML") 
  {
    full_name_ = "Chain Mail";
    armor_value_ = 6;
  } 
  else if (item == "PARM") 
  {
    full_name_ = "Plate Armor";
    armor_value_ = 8;
  }
}

///---------------------------------------------------------------------------------------------------------------------
Weapon::Weapon(std::string item, int amount) 
{
  amount_ = amount;
  abbreviation_ = item;
  type_ = ItemType::WEAPON;
  lich_ = false;

  if (item == "DAGG") 
  {
    full_name_ = "Dagger";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::HIT;
    dice_amount_ = 1;
    damage_per_dice_ = 4;
    str_based_ = false;
    staff_ = false;
  } 
  else if (item == "MACE") 
  {
    full_name_ = "Mace";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::HIT;
    dice_amount_ = 1;
    damage_per_dice_ = 6;
    str_based_ = true;
    staff_ = false;
  } 
  else if (item == "WARH") 
  {
    full_name_ = "Warhammer";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::HIT;
    dice_amount_ = 1;
    damage_per_dice_ = 10;
    str_based_ = true;
    staff_ = false;
  } 
  else if (item == "HAXE") 
  {
    full_name_ = "Handaxe";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::HIT;
    dice_amount_ = 1;
    damage_per_dice_ = 6;
    str_based_ = true;
    staff_ = false;
  } 
  else if (item == "GAXE") 
  {
    full_name_ = "Greataxe";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::SLASH;
    dice_amount_ = 1;
    damage_per_dice_ = 12;
    str_based_ = true;
    staff_ = false;
  } 
  else if (item == "RAPI") 
  {
    full_name_ = "Rapier";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::THRUST;
    dice_amount_ = 1;
    damage_per_dice_ = 8;
    str_based_ = false;
    staff_ = false;
  } 
  else if (item == "SSWD") 
  {
    full_name_ = "Shortsword";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::THRUST;
    dice_amount_ = 1;
    damage_per_dice_ = 6;
    str_based_ = false;
    staff_ = false;
  } 
  else if (item == "LSWD") 
  {
    full_name_ = "Longsword";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::SLASH;
    dice_amount_ = 1;
    damage_per_dice_ = 10;
    str_based_ = true;
    staff_ = false;
  } 
  else if (item == "GSWD") 
  {
    full_name_ = "Greatsword";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::SLASH;
    dice_amount_ = 2;
    damage_per_dice_ = 6;
    str_based_ = true;
    staff_ = false;
  } 
  else if (item == "SBOW") 
  {
    full_name_ = "Shortbow";
    attack_type_ = AttackType::RANGED;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::SHOT;
    dice_amount_ = 1;
    damage_per_dice_ = 6;
    str_based_ = false;
    staff_ = false;
  } 
  else if (item == "LBOW") 
  {
    full_name_ = "Longbow";
    attack_type_ = AttackType::RANGED;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::SHOT;
    dice_amount_ = 1;
    damage_per_dice_ = 8;
    str_based_ = false;
    staff_ = false;
  } 
  else if (item == "LCRS") 
  {
    full_name_ = "Light Crossbow";
    attack_type_ = AttackType::RANGED;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::SHOT;
    dice_amount_ = 1;
    damage_per_dice_ = 8;
    str_based_ = false;
    staff_ = false;
  } 
  else if (item == "HCRS") 
  {
    full_name_ = "Heavy Crossbow";
    attack_type_ = AttackType::RANGED;
    dmg_type_ = Item::DamageType::PHYSICAL;
    dmg_pattern_ = DamagePattern::SHOT;
    dice_amount_ = 1;
    damage_per_dice_ = 10;
    str_based_ = false;
    staff_ = false;
  } 
  else if (item == "QFIR") 
  {
    full_name_ = "Quarterstaff of Fire";
    attack_type_ = AttackType::RANGED;
    dmg_type_ = Item::DamageType::FIRE;
    dmg_pattern_ = DamagePattern::BURST;
    dice_amount_ = 3;
    damage_per_dice_ = 6;
    str_based_ = true;
    staff_ = true;
  } 
  else if (item == "QCLD") 
  {
    full_name_ = "Quarterstaff of Cold";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::COLD;
    dmg_pattern_ = DamagePattern::LINE;
    dice_amount_ = 2;
    damage_per_dice_ = 10;
    str_based_ = true;
    staff_ = true;
  } 
  else if (item == "QACD") 
  {
    full_name_ = "Quarterstaff of Acid";
    attack_type_ = AttackType::RANGED;
    dmg_type_ = Item::DamageType::ACID;
    dmg_pattern_ = DamagePattern::SHOT;
    dice_amount_ = 1;
    damage_per_dice_ = 10;
    str_based_ = true;
    staff_ = true;
  } 
  else if (item == "QFRC") 
  {
    full_name_ = "Quarterstaff of Force";
    attack_type_ = AttackType::MELEE;
    dmg_type_ = Item::DamageType::FORCE;
    dmg_pattern_ = DamagePattern::HIT;
    dice_amount_ = 1;
    damage_per_dice_ = 10;
    str_based_ = true;
    staff_ = true;
  } 
}

///---------------------------------------------------------------------------------------------------------------------
bool compareFieldColumn(Field* field1, Field* field2)
{
  return (field1->getCoordinates()[1] < field2->getCoordinates()[1]);
}

///---------------------------------------------------------------------------------------------------------------------
bool compareFieldRow(Field* field1, Field* field2)
{
  return (field1->getCoordinates()[0] < field2->getCoordinates()[0]);
}

///---------------------------------------------------------------------------------------------------------------------
void Weapon::calculateDamage(Character* character, Field* char_field, int damage)
{
  float resist_factor = 1;

  int char_av = character->getArmorValue();

  Item::DamageType char_resist = character->getResistance();

  if (dmg_type_ == char_resist)
    resist_factor = 0.5;

  std::string resist_string;

  if (resist_factor == 1)
    resist_string = "100";
  else
    resist_string = "50";

  int final_damage = (damage * resist_factor) - char_av;

  if (final_damage < 0)
    final_damage = 0;

  if (final_damage > character->getHP()) 
  {
    final_damage = character->getHP();
    character->setHP(0);
  } 
  else 
  {
    character->setHP(character->getHP() - final_damage);
  }

  if (character->getCharType() == Entity::CharacterType::GOBLIN ||
      character->getCharType() == Entity::CharacterType::ZOMBIE ||
      character->getCharType() == Entity::CharacterType::LICH)
    std::cout << character->getFullName() << " " << character->getId();
  else
    std::cout << character->getPlayer()->getName();

  std::cout << " loses " << final_damage << " health (" << damage << " * ";
  std::cout << resist_string << " % - " << char_av << ")." << std::endl;

  if (character->getHP() == 0)
  {
    if (character->getCharType() == Entity::CharacterType::GOBLIN ||
        character->getCharType() == Entity::CharacterType::ZOMBIE ||
        character->getCharType() == Entity::CharacterType::LICH)
      std::cout << character->getFullName() << " " << character->getId();
    else
      std::cout << character->getPlayer()->getName();

    std::cout << " was defeated." << std::endl;

    if (character->getCharType() == Entity::CharacterType::LICH)
      lich_ = true;
      
    char_field->convertCharToDL(character);
  }
}

///---------------------------------------------------------------------------------------------------------------------
bool Item::allPlayersDead(std::vector<Player *> players) 
{
  int count = 0;
  for (Player *player : players) 
  {
    if (player->getCharacter()->isAlive()) 
    {
      count++;
    }
  }

  return (count == 0);
}

///---------------------------------------------------------------------------------------------------------------------
void Weapon::applyDamage(std::vector<Field*>& affected_fields, Character* attacker, 
                        std::vector<int>& target_cords, int dmg_mod, std::vector<Player *> players)
{
  std::sort(affected_fields.begin(), affected_fields.end(), compareFieldColumn);
  std::sort(affected_fields.begin(), affected_fields.end(), compareFieldRow);

  if (attacker->getPlayer() != nullptr)
  {
    Player* player = attacker->getPlayer();
    std::cout << attacker->getFullName() << " [" << static_cast<char>(attacker->getCharType()) << "] ";
    std::cout << "\"" << player->getName() << "\" ";
  }
  else
  {
    std::cout << "\n" << attacker->getFullName() << " " << attacker->getId() << " ";
    std::cout << "[" << static_cast<char>(attacker->getCharType()) << attacker->getId() << "] ";
  }

  std::cout << "used \"";
  std::cout << getName() << "\" on (" << target_cords[0] + 1 << "," << target_cords[1] + 1 << ") ";
  std::cout << "affecting";

  for (Field* field : affected_fields)
  {
    std::cout << " (" << field->getCoordinates()[0] << "," << field->getCoordinates()[1] << ")";
    if (field != affected_fields.back())
      std::cout << ",";
  }

  std::cout << "." <<std::endl;

  int damage;

  if (staff_  &&
      attacker->getCharType() != Entity::CharacterType::WIZARD &&
      attacker->getCharType() != Entity::CharacterType::LICH)
    damage = Game::rollDice(1, 6) + dmg_mod;
  else
    damage = Game::rollDice(dice_amount_, damage_per_dice_) + dmg_mod;

  for (Field* field : affected_fields)
  {
    if (allPlayersDead(players) || lich_) 
    {
      return;
    }

    if (field->getEntity() != nullptr && field->getEntity()->getEntityType() == Entity::EntityType::CHARACHTER) 
    {
      calculateDamage(static_cast<Character*>(field->getEntity()), field, damage);
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Weapon::slashDmgPattern(std::vector<int>& attacker_cords, 
                             std::vector<int>& target_cords, Room* room, 
                             std::vector<Field*>& affected_fields)
{
  std::vector<std::vector<Field*>> fields = room->getFields();

  int attacker_row = attacker_cords[0];
  int attacker_column = attacker_cords[1];
  int target_row = target_cords[0];
  int target_column = target_cords[1];

  int sub_target1_row = target_row;
  int sub_target1_column = target_column;
  int sub_target2_row = target_row;
  int sub_target2_column = target_column;

  if (attacker_row - target_row == 1 &&
      attacker_column - target_column == 1)
  {
    sub_target1_row = target_row + 1;
    sub_target2_column = target_column + 1;
  }
  else if (attacker_row - target_row == -1 &&
           attacker_column - target_column == 1)
  {
    sub_target1_row = target_row - 1;
    sub_target2_column = target_column + 1;
  }
  else if (attacker_row - target_row == -1 &&
           attacker_column - target_column == -1)
  {
    sub_target1_row = target_row - 1;
    sub_target2_column = target_column - 1;
  }
  else if (attacker_row - target_row == 1 &&
           attacker_column - target_column == -1)
  {
    sub_target1_row = target_row + 1;
    sub_target2_column = target_column - 1;
  }
  else if ((attacker_row - target_row == 1 || attacker_row - target_row == -1) &&
            attacker_column - target_column == 0)
  {
    sub_target1_column = target_column - 1;
    sub_target2_column = target_column + 1;
  }
  else if (attacker_row - target_row == 0 &&
          (attacker_column - target_column == 1 || attacker_column - target_column == -1))
  {
    sub_target1_row = target_row - 1;
    sub_target2_row = target_row + 1;
  }

  if ((sub_target1_row < int(fields.size()) && sub_target1_row >= 0) &&
      (sub_target1_column < int(fields[0].size()) && sub_target1_column >= 0))
  {
    Field* affected_field = fields[sub_target1_row][sub_target1_column];
    affected_fields.push_back(affected_field);
  }

  if ((sub_target2_row < int(fields.size()) && sub_target2_row >= 0) &&
      (sub_target2_column < int(fields[0].size()) && sub_target2_column >= 0))
  {
    Field* affected_field = fields[sub_target2_row][sub_target2_column];
    affected_fields.push_back(affected_field);
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Weapon::thrustDmgPattern(std::vector<int>& attacker_cords, 
                             std::vector<int>& target_cords, Room* room, 
                             std::vector<Field*>& affected_fields)
{
  std::vector<std::vector<Field*>> fields = room->getFields();

  int attacker_row = attacker_cords[0];
  int attacker_column = attacker_cords[1];
  int target_row = target_cords[0];
  int target_column = target_cords[1];

  int sub_target_row = target_row;
  int sub_target_column = target_column;

  if (attacker_row - target_row == 1 &&
      attacker_column - target_column == 1)
  {
    sub_target_row = target_row - 1;
    sub_target_column = target_column - 1;
  }
  else if (attacker_row - target_row == -1 &&
           attacker_column - target_column == 1)
  {
    sub_target_row = target_row + 1;
    sub_target_column = target_column - 1;
  }
  else if (attacker_row - target_row == -1 &&
           attacker_column - target_column == -1)
  {
    sub_target_row = target_row + 1;
    sub_target_column = target_column + 1;
  }
  else if (attacker_row - target_row == 1 &&
           attacker_column - target_column == -1)
  {
    sub_target_row = target_row - 1;
    sub_target_column = target_column + 1;
  }
  else if (attacker_row - target_row == 1 &&
           attacker_column - target_column == 0)
  {
    sub_target_row = target_row - 1;
  }
  else if (attacker_row - target_row == -1 &&
           attacker_column - target_column == 0)
  {
    sub_target_row = target_row + 1;
  }
  else if (attacker_row - target_row == 0 &&
           attacker_column - target_column == -1)
  {
    sub_target_column = target_column + 1;
  }
  else if (attacker_row - target_row == 0 &&
           attacker_column - target_column == 1)
  {
    sub_target_column = target_column - 1;
  }

  if ((sub_target_row < int(fields.size()) && sub_target_row >= 0) &&
      (sub_target_column < int(fields[0].size()) && sub_target_column >= 0))
  {
    Field* affected_field = fields[sub_target_row][sub_target_column];
    affected_fields.push_back(affected_field);
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Item::setAmount(int amount) 
{
  amount_ = amount_ + amount;
}

///---------------------------------------------------------------------------------------------------------------------
void Weapon::lineDmgPattern(std::vector<int>& attacker_cords, 
                             std::vector<int>& target_cords, Room* room, 
                             std::vector<Field*>& affected_fields)
{
  std::vector<std::vector<Field*>> fields = room->getFields();
  int num_rows = room->getRows();
  int num_columns = room->getColumns();

  int attacker_row = attacker_cords[0];
  int attacker_column = attacker_cords[1];
  int target_row = target_cords[0];
  int target_column = target_cords[1];

  std::vector<int> sub_targets_rows;
  std::vector<int> sub_targets_columns;

  if (attacker_row - target_row == 1 && attacker_column - target_column == 1) 
  {
    sub_targets_rows.push_back(target_row - 1);
    sub_targets_columns.push_back(target_column - 1);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(sub_targets_rows[i-1] - 1);
      sub_targets_columns.push_back(sub_targets_columns[i-1] - 1);
    }
  }

  if (attacker_row - target_row == 1 && attacker_column - target_column == -1) 
  {
    sub_targets_rows.push_back(target_row - 1);
    sub_targets_columns.push_back(target_column + 1);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(sub_targets_rows[i-1] - 1);
      sub_targets_columns.push_back(sub_targets_columns[i-1] + 1);
    }
  }

  if (attacker_row - target_row == -1 && attacker_column - target_column == -1) 
  {
    sub_targets_rows.push_back(target_row + 1);
    sub_targets_columns.push_back(target_column + 1);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(sub_targets_rows[i-1] + 1);
      sub_targets_columns.push_back(sub_targets_columns[i-1] + 1);
    }
  }

  if (attacker_row - target_row == -1 && attacker_column - target_column == 1) 
  {
    sub_targets_rows.push_back(target_row + 1);
    sub_targets_columns.push_back(target_column - 1);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(sub_targets_rows[i-1] + 1);
      sub_targets_columns.push_back(sub_targets_columns[i-1] - 1);
    }
  }

  else if (attacker_row - target_row == 0 && attacker_column - target_column == 1) 
  {
    sub_targets_rows.push_back(target_row);
    sub_targets_columns.push_back(target_column - 1);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(target_row);
      sub_targets_columns.push_back(sub_targets_columns[i-1] - 1);
    }
  }

  else if (attacker_row - target_row == 0 && attacker_column - target_column == -1) 
  {
    sub_targets_rows.push_back(target_row);
    sub_targets_columns.push_back(target_column + 1);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(target_row);
      sub_targets_columns.push_back(sub_targets_columns[i-1] + 1);
    }
  }

  else if (attacker_row - target_row == 1 && attacker_column - target_column == 0) 
  {
    sub_targets_rows.push_back(target_row - 1);
    sub_targets_columns.push_back(target_column);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(sub_targets_rows[i-1] - 1);
      sub_targets_columns.push_back(target_column);
    }
  }

  else if (attacker_row - target_row == -1 && attacker_column - target_column == 0) 
  {
    sub_targets_rows.push_back(target_row + 1);
    sub_targets_columns.push_back(target_column);
    for (int i = 1; i <= num_rows && i <= num_columns; i++) 
    {
      sub_targets_rows.push_back(sub_targets_rows[i-1] + 1);
      sub_targets_columns.push_back(target_column);
    }
  }

  for (std::size_t i = 0; i < sub_targets_rows.size() && i < sub_targets_columns.size(); i++)
  {
    int row = sub_targets_rows[i];
    int col = sub_targets_columns[i];

    if (row >= 0 && row < num_rows && col >= 0 && col < num_columns) 
    {
      Field* affected_field = fields[row][col];
      affected_fields.push_back(affected_field);
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Weapon::burstDmgPattern(std::vector<int>& target_cords, Room* room, std::vector<Field*>& affected_fields)
{
  std::vector<std::vector<Field*>> fields = room->getFields();

  int target_row = target_cords[0];
  int target_column = target_cords[1];

  int num_rows = fields.size();
  int num_columns = num_rows > 0 ? fields[0].size() : 0;

  if (target_row - 1 >= 0 && target_row - 1 < num_rows &&
    target_column >= 0 && target_column < num_columns)
  {
    Field* affected_field = fields[target_row - 1][target_column];
    affected_fields.push_back(affected_field);
  }

  if (target_row >= 0 && target_row < num_rows &&
    target_column + 1 >= 0 && target_column + 1 < num_columns)
  {
    Field* affected_field = fields[target_row][target_column + 1];
    affected_fields.push_back(affected_field);
  }

  if (target_row + 1 >= 0 && target_row + 1 < num_rows &&
    target_column >= 0 && target_column < num_columns)
  {
    Field* affected_field = fields[target_row + 1][target_column];
    affected_fields.push_back(affected_field);
  }

  if (target_row >= 0 && target_row < num_rows &&
    target_column - 1 >= 0 && target_column - 1 < num_columns)
  {
    Field* affected_field = fields[target_row][target_column - 1];
    affected_fields.push_back(affected_field);
  }
}

///---------------------------------------------------------------------------------------------------------------------
bool Weapon::attackForStaff(Character* attacker, Field* target, Room* room,std::vector<Player *> players)
{
  std::vector<int> attacker_coordinates = attacker->getCoordinates();
  std::vector<int> target_coordinates = target->getCoordinates();

  target_coordinates[0]--;
  target_coordinates[1]--;

  std::vector<Field*> affected_fields;

  int dmg_mod;
  if (attacker->getCharType() == Entity::CharacterType::WIZARD || 
      attacker->getCharType() == Entity::CharacterType::LICH)
  {
    dmg_mod = 0;
  }
  else
  {
    dmg_mod = attacker->getStrength();

    if (std::abs(target_coordinates[0] - attacker_coordinates[0]) > 1 ||
        std::abs(target_coordinates[1] - attacker_coordinates[1]) > 1)
      return false;
    affected_fields.push_back(target);
    applyDamage(affected_fields, attacker, target_coordinates, dmg_mod, players);
    return true;
  }

  if (attack_type_ == AttackType::MELEE)
  {
    if (std::abs(target_coordinates[0] - attacker_coordinates[0]) > 1 ||
        std::abs(target_coordinates[1] - attacker_coordinates[1]) > 1)
      return false;
    affected_fields.push_back(target);

    switch (dmg_pattern_)
    {
    case DamagePattern::HIT:
      break;
    case DamagePattern::LINE:
      lineDmgPattern(attacker_coordinates, target_coordinates, room, affected_fields);
      break;
    default:
      break;
    }

    applyDamage(affected_fields, attacker, target_coordinates, dmg_mod, players);
  }
  else
  {
    affected_fields.push_back(target);

    switch (dmg_pattern_)
    {
    case DamagePattern::SHOT:
      break;
    case DamagePattern::BURST:
      burstDmgPattern(target_coordinates, room, affected_fields);
      break;
    default:
      break;
    }

    applyDamage(affected_fields, attacker, target_coordinates, dmg_mod, players);
  }

  return true;
}

///---------------------------------------------------------------------------------------------------------------------
bool Weapon::attackForMelee(Character* attacker, Field* target, Room* room, std::vector<Player *> players)
{
  std::vector<int> attacker_coordinates = attacker->getCoordinates();
  std::vector<int> target_coordinates = target->getCoordinates();

  target_coordinates[0]--;
  target_coordinates[1]--;

  if (std::abs(target_coordinates[0] - attacker_coordinates[0]) > 1 ||
      std::abs(target_coordinates[1] - attacker_coordinates[1]) > 1)
    return false;

  std::vector<Field*> affected_fields;

  affected_fields.push_back(target);

  int dmg_mod;
  if (str_based_)
    dmg_mod = attacker->getStrength();
  else
    dmg_mod = attacker->getVitality();

  switch (dmg_pattern_)
  {
  case DamagePattern::HIT:
    break;
  case DamagePattern::SLASH:
    slashDmgPattern(attacker_coordinates, target_coordinates, room, affected_fields);
    break;
  case DamagePattern::THRUST:
    thrustDmgPattern(attacker_coordinates, target_coordinates, room, affected_fields);
    break;
  case DamagePattern::LINE:
    std::cout << "check" << std::endl;
    lineDmgPattern(attacker_coordinates, target_coordinates, room, affected_fields);
    break;
  default:
    break;
  }

  applyDamage(affected_fields, attacker, target_coordinates, dmg_mod, players);

  return true;
}

///---------------------------------------------------------------------------------------------------------------------
bool Weapon::attackForRanged(Character* attacker, Field* target, Room* room, std::vector<Player *> players)
{
  Item* temp_item = nullptr;

  for (Item* item : attacker->getInventory())
  {
    if (item->getAbbreviation() == "ARRW" && attacker->getPlayer() != nullptr)
    {
      if (item->getAmount() <= 0 &&
          (Item::abbreviation_ == "SBOW" || Item::abbreviation_ == "LBOW"))
        return false;
      else if (item->getAmount() >= 0 &&
               (Item::abbreviation_ == "SBOW" || Item::abbreviation_ == "LBOW"))
      {
        temp_item = item;
        break;
      }
    }
    if (item->getAbbreviation() == "BOLT" && attacker->getPlayer() != nullptr)
    {
      if (item->getAmount() <= 0 &&
          (Item::abbreviation_ == "LCRS" || Item::abbreviation_ == "HCRS"))
        return false;
      else if (item->getAmount() >= 0 &&
               (Item::abbreviation_ == "LCRS" || Item::abbreviation_ == "HCRS"))
      {
        temp_item = item;
        break;
      }
    }
  }

  if (attacker->getPlayer() != nullptr && temp_item == nullptr)
    return false;

  std::vector<int> attacker_coordinates = attacker->getCoordinates();
  std::vector<int> target_coordinates = target->getCoordinates();

  target_coordinates[0]--;
  target_coordinates[1]--;

  std::vector<Field*> affected_fields;

  affected_fields.push_back(target);

  int dmg_mod;
  if (str_based_)
    dmg_mod = attacker->getStrength();
  else
    dmg_mod = attacker->getVitality();

  switch (dmg_pattern_)
  {
  case DamagePattern::SHOT:
    break;
  case DamagePattern::BURST:
    burstDmgPattern(target_coordinates, room, affected_fields);
    break;
  default:
    break;
  }

  applyDamage(affected_fields, attacker, target_coordinates, dmg_mod, players);

  if (attacker->getPlayer() != nullptr &&
      (Item::abbreviation_ == "SBOW" || Item::abbreviation_ == "LBOW"))
  {
    for (Item* arrow : attacker->getInventory())
    {
      if (arrow->getAbbreviation() == "ARRW")
        arrow->setAmount(-static_cast<int>(affected_fields.size()));
      if (arrow->getAbbreviation() == "ARRW" && arrow->getAmount() <= 0) 
      {
        attacker->eraseItem(arrow);
        delete arrow;
      }  
    }
  }
  else if (attacker->getPlayer() != nullptr &&
      (Item::abbreviation_ == "LCRS" || Item::abbreviation_ == "HCRS"))
  {
    for (Item* bolt : attacker->getInventory())
    {
      if (bolt->getAbbreviation() == "BOLT")
        bolt->setAmount(-static_cast<int>(affected_fields.size()));
      if (bolt->getAbbreviation() == "BOLT" && bolt->getAmount() <= 0) 
      {
        attacker->eraseItem(bolt);
        delete bolt;
      }
    }
  }

  return true;
}

///---------------------------------------------------------------------------------------------------------------------
Command::Errors Weapon::attackTarget(Character* attacker, Field* target, Room* room, std::vector<Player *> players)
{
  if (staff_)
  {
    if (!attackForStaff(attacker, target, room, players))
      return Command::Errors::INVALID_POSITION;
  }
  else
  {
    if (attack_type_ == AttackType::MELEE)
    {
      if (!attackForMelee(attacker, target, room, players))
        return Command::Errors::INVALID_POSITION;
    }
    else if (attack_type_ == AttackType::RANGED)
    {
      if (!attackForRanged(attacker, target, room, players))
        return Command::Errors::ATTACK_NO_AMMUNITION;
    }
  }

  return Command::Errors::NO_ERROR;
}

///---------------------------------------------------------------------------------------------------------------------
void Armor::applyArmor(Character* character)
{
  if (Item::getAbbreviation() == "LARM")
  {
    character->setArmorValue(armor_value_ + character->getVitality());
  }
  else if (Item::getAbbreviation() == "BPLT")
  {
    int max_vit_scaling = character->getVitality();

    if (max_vit_scaling > 2)
      max_vit_scaling = 2;

    character->setArmorValue(armor_value_ + max_vit_scaling);
  }
  else if (Item::getAbbreviation() == "CHML" || Item::getAbbreviation() == "PARM")
  {
    character->setArmorValue(armor_value_);
  }
}

///---------------------------------------------------------------------------------------------------------------------
int HealthPotions::restoreHealth(Character* character)
{
  int restored_health = Game::rollDice(dice_amount_, 4);

  int new_health = character->getHP() + restored_health;

  if (new_health > character->getMaxHP())
  {
    restored_health = restored_health - (new_health - character->getMaxHP());
    new_health = character->getMaxHP();
  }

  character->setHP(new_health);

  return restored_health;
}

///---------------------------------------------------------------------------------------------------------------------
void ResistPotions::applyResist(Character* character)
{
  character->setResistance(resist_type_);
}

///---------------------------------------------------------------------------------------------------------------------
Weapon::AttackType Weapon::getAttackType() { 
  return attack_type_; 
}

///---------------------------------------------------------------------------------------------------------------------
int Item::getAmount() const
{ 
  return amount_; 
}

///---------------------------------------------------------------------------------------------------------------------
std::string Item::getName() const 
{ 
  return full_name_; 
}

///---------------------------------------------------------------------------------------------------------------------
std::string Item::getAbbreviation() const
{ 
  return abbreviation_; 
}
 
///---------------------------------------------------------------------------------------------------------------------
Item::ItemType Item::getItemType() 
{ 
  return type_ ;
}

///---------------------------------------------------------------------------------------------------------------------
int Armor::getArmorValue()
{
  return armor_value_;
}

///---------------------------------------------------------------------------------------------------------------------
Item::DamageType ResistPotions::getResistType() const 
{ 
  return resist_type_; 
}
