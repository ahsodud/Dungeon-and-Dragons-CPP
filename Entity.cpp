///---------------------------------------------------------------------------------------------------------------------
/// Entity.cpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#include "Entity.hpp"
#include "Room.hpp"
#include "Field.hpp"
#include "Random.hpp"
#include "Player.hpp"

///---------------------------------------------------------------------------------------------------------------------
DeathLocation::DeathLocation(std::vector<Item *> loot, std::vector<int> coordinates) : loot_(loot) 
{
  type_ = EntityType::DEATH_LOCATION;
  coordinates_ = coordinates;
}

///---------------------------------------------------------------------------------------------------------------------
Entity::EntityType Entity::getEntityType(void) 
{
  return type_;
}

///---------------------------------------------------------------------------------------------------------------------
Entity::CharacterType Entity::getCharType(void) const 
{ 
  return char_type_; 
}

///---------------------------------------------------------------------------------------------------------------------
int Entity::getId(void) const
{
  return id_;
}

///---------------------------------------------------------------------------------------------------------------------
Character::Character(char letter, Player* player)
{
  type_ = Entity::EntityType::CHARACHTER;
  player_ = player;
  equipped_armor_ = nullptr;
  equipped_weapon_ = nullptr;

  switch(letter)
  {
    case 'B':
    {
      char_type_ = CharacterType::BARBARIAN;
      strength_ = 4;
      vitality_ = 1;
      base_hp_ = 12;
      calculateMaxHp();
      hp_ = max_hp_;
      base_armor_value_ = 2;
      armor_value_ = base_armor_value_;
      resistance_ = Item::DamageType::NONE;

      Item *new_weapon2 = new Weapon("HAXE", 2);
      weapons_.push_back(new_weapon2);

      Item *new_weapon = new Weapon("GAXE", 1);
      equipped_weapon_ = new_weapon;


      equipped_armor_ = NULL;
      break;
    }
    case 'W':
    {
      char_type_ = CharacterType::WIZARD;
      strength_ = 1;
      vitality_ = 4;
      base_hp_ = 6;
      calculateMaxHp();
      hp_ = max_hp_;
      base_armor_value_ = 0;
      armor_value_ = base_armor_value_;

      Item *new_weapon = new Weapon("QFRC", 1);
      equipped_weapon_ = new_weapon;

      Item *new_weapon1 = new Weapon("QACD", 1);
      weapons_.push_back(new_weapon1);

      Item *new_weapon2 = new Weapon("DAGG", 1);
      weapons_.push_back(new_weapon2);

      resistance_ = Item::DamageType::NONE;
      break;
    }
    case 'R':
    {
      char_type_ = CharacterType::ROGUE;
      strength_ = 2;
      vitality_ = 3;
      base_hp_ = 8;
      calculateMaxHp();
      hp_ = max_hp_;
      base_armor_value_ = 1;

      Item *new_armor = new Armor("LARM", 1);
      equipped_armor_ = new_armor;
      static_cast<Armor*>(equipped_armor_)->applyArmor(this);

      Item *new_weapon2 = new Weapon("DAGG", 2);
      weapons_.push_back(new_weapon2);

      Item *new_weapon = new Weapon("RAPI", 1);
      equipped_weapon_ = new_weapon;

      Item *new_weapon1 = new Weapon("SBOW", 1);
      weapons_.push_back(new_weapon1);

      Item *new_consumable = new Ammunition("ARRW", 20);
      inventory_.push_back(new_consumable);

      resistance_ = Item::DamageType::NONE;
      break;
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Character::calculateMaxHp() 
{
  max_hp_ = base_hp_ + vitality_;
}

///---------------------------------------------------------------------------------------------------------------------
void Character::AdjustArmorValue(int input_value)
{
  armor_value_ = armor_value_ + input_value;
} 

///---------------------------------------------------------------------------------------------------------------------
void Character::calculateArmor(int input_value) 
{      
  armor_value_ = base_armor_value_ + input_value;
}

///---------------------------------------------------------------------------------------------------------------------
void Character::clearInventory() 
{
  inventory_.clear();
  equipped_armor_ = nullptr;
  equipped_weapon_ = nullptr;
  weapons_.clear();
  armor_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
Character::Character(char letter, int enemy_id) 
{
  type_ = Entity::EntityType::CHARACHTER;
  equipped_armor_ = nullptr;
  equipped_weapon_ = nullptr;
  id_ = enemy_id;
  player_ = nullptr;

  switch(letter)
  {
    case 'G':
    {
      char_type_ = CharacterType::GOBLIN;
      hp_ = 10;
      max_hp_ = 10;
      armor_value_ = 4;
      strength_ = 3;
      vitality_ = 4;
      resistance_ = Item::DamageType::NONE;

      Item *weapon_1 = new Weapon("HAXE", 1);
      Item *weapon_2 = new Weapon("SBOW", 1);
      weapons_.push_back(weapon_1);
      weapons_.push_back(weapon_2);

      Item *arrows = new Ammunition("ARRW", 3);
      inventory_.push_back(arrows);

      break;
    }
    case 'L':
    {
      char_type_ = CharacterType::LICH;
      hp_ = 50;
      max_hp_ = 50;
      armor_value_ = 6;
      strength_ = 2;
      vitality_ = 8;
      resistance_ = Item::DamageType::COLD;
      
      Item *weapon_1 = new Weapon("QFIR", 1);
      Item *weapon_2 = new Weapon("QCLD", 1);
      Item *weapon_3 = new Weapon("QACD", 1);
      Item *weapon_4 = new Weapon("QFRC", 1);

      weapons_.push_back(weapon_1);
      weapons_.push_back(weapon_2);
      weapons_.push_back(weapon_3);
      weapons_.push_back(weapon_4);
      
      break;
    }
    case 'Z':
    {
      char_type_ = CharacterType::ZOMBIE;
      hp_ = 15;
      max_hp_ = 15;
      armor_value_ = 1;
      strength_ = 3;
      vitality_ = 0;
      resistance_ = Item::DamageType::NONE;

      Item *weapon = new Weapon("DAGG", 1);
      weapons_.push_back(weapon);
      
      break;
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
Character::~Character()
{
  for (auto item : inventory_) 
  {
    delete item;
  }
  for (auto weapon : weapons_) 
  {
    delete weapon;
  }
  for (auto armor : armor_) 
  {
    delete armor;
  }
  // Delete equipped items if they are not nullptr
  delete equipped_weapon_;
  delete equipped_armor_;
}

///---------------------------------------------------------------------------------------------------------------------
int Character::getMaxHP() const 
{ 
  return max_hp_; 
}

///---------------------------------------------------------------------------------------------------------------------
int Character::getHP() const 
{ 
  return hp_; 
}

///---------------------------------------------------------------------------------------------------------------------
int Character::getArmorValue() const 
{ 
  return armor_value_; 
}

///---------------------------------------------------------------------------------------------------------------------
int Character::getStrength() const 
{ 
  return strength_; 
}

///---------------------------------------------------------------------------------------------------------------------
int Character::getVitality() const 
{ 
  return vitality_; 
}

///---------------------------------------------------------------------------------------------------------------------
Item::DamageType Character::getResistance() const 
{ 
  return resistance_; 
}

///---------------------------------------------------------------------------------------------------------------------
const std::vector<Item*> Character::getInventory() 
{ 
  return inventory_; 
}

///---------------------------------------------------------------------------------------------------------------------
const std::vector<Item*> Character::getWeapons() 
{ 
  return weapons_; 
}

///---------------------------------------------------------------------------------------------------------------------
const std::vector<Item*> Character::getArmor() 
{ 
  return armor_; 
}

///---------------------------------------------------------------------------------------------------------------------
Item* Character::getEquippedWeapon() const
{ 
  return equipped_weapon_;
}

///---------------------------------------------------------------------------------------------------------------------
Item* Character::getEquippedArmor() const
{ 
  return equipped_armor_;
}

///---------------------------------------------------------------------------------------------------------------------
Player* Character::getPlayer() const 
{ 
  return player_; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setCharType(CharacterType char_type) 
{ 
  char_type_ = char_type;
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setMaxHP(int max_hp) 
{ 
  max_hp_ = max_hp; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setHP(int hp) 
{ 
  hp_ = hp; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setArmorValue(int armor_value) 
{ 
  armor_value_ = armor_value; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setStrength(int strength) 
{ 
  strength_ = strength; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setVitality(int vitality) 
{ 
  vitality_ = vitality; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setResistance(Item::DamageType resistance) 
{ 
  resistance_ = resistance; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setEquippedWeapon(Item* weapon) 
{ 
  equipped_weapon_ = weapon; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::setEquippedArmor(Item* armor) 
{ 
  equipped_armor_ = armor; 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::addItem(Item* item) 
{ 
  inventory_.push_back(item); 
}

///---------------------------------------------------------------------------------------------------------------------
void Character::lootArmor(std::vector<Item *> items) 
{
  for (Item *item : items) 
  {
    if (findItem(armor_, item)) 
    {
      addFoundItem(armor_, item);
      delete item;
    }
    else 
    {
      armor_.push_back(item);
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Character::lootWeapons(std::vector<Item *> items) 
{
  for (auto& item : items) 
  {
    if (findItem(weapons_, item)) 
    {
      addFoundItem(weapons_, item);
      delete item;
    }
    else 
    {
      weapons_.push_back(item);
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Character::lootConsumables(std::vector<Item *> items) 
{
  for (auto& item : items) 
  {
    if (findItem(inventory_, item)) 
    {
      addFoundItem(inventory_, item);
      delete item;
    }
    else 
    {
      inventory_.push_back(item);
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
bool Character::findItem(std::vector<Item *> vector, Item *item) 
{
  std::string abbr = item->getAbbreviation();

  for (auto i : vector) 
  {
    if (i->getAbbreviation() == abbr) 
    {
      return true;
    }
  }

  return false;
}

///---------------------------------------------------------------------------------------------------------------------
void Character::eraseWeapon(Item *weapon) 
{
  int size = weapons_.size();
  int index;

  for (int i = 0; i < size; i++) 
  {
    if (weapons_[i]->getAbbreviation() == weapon->getAbbreviation()) 
    {
      index = i;
    }
  }

  weapons_.erase(weapons_.begin() + index);
}

///---------------------------------------------------------------------------------------------------------------------
void Character::addWeapon(Item * weapon) 
{
  weapons_.push_back(weapon);
}

///---------------------------------------------------------------------------------------------------------------------
void Character::addArmor(Item *armor) 
{
  armor_.push_back(armor);
}

///---------------------------------------------------------------------------------------------------------------------
void Character::eraseArmor(Item *armor) 
{
  int size = armor_.size();
  int index;

  for (int i = 0; i < size; i++) 
  {
    if (armor_[i]->getAbbreviation() == armor->getAbbreviation()) 
    {
      index = i;
    }
  }

  armor_.erase(armor_.begin() + index);
}

///---------------------------------------------------------------------------------------------------------------------
void Character::eraseItem(Item *item) 
{
  int size = inventory_.size();
  int index;

  for (int i = 0; i < size; i++) 
  {
    if (inventory_[i]->getAbbreviation() == item->getAbbreviation()) 
    {
      index = i;
    }
  }

  inventory_.erase(inventory_.begin() + index);
}

///---------------------------------------------------------------------------------------------------------------------
void Character::addFoundItem(std::vector<Item *> vector, Item* item) 
{
  std::string abbr = item->getAbbreviation();

  for (auto i : vector) 
  {
    if (i->getAbbreviation() == abbr) 
    {
      i->setAmount(item->getAmount());
      return;
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
bool Character::isAlive() 
{
  return hp_ > 0;
}

///---------------------------------------------------------------------------------------------------------------------
bool Character::attack(Room *room, std::vector<Player *> players, std::vector<std::vector<Field *>> fields) 
{
  std::vector<int> attack_coords(2);
  Character *character;

  int index = 0;
  if (players.size() > 1) 
  {
    index = findTarget(players);
    if (index == 100) 
    {
      return false;
    }
  }

  attack_coords = players[index]->getCharacter()->getCoordinates();
  character = players[index]->getCharacter();
  //std::cout << "Attack: " << players[index]->getName() << std::endl;

  Weapon *weapon = nullptr;
  if (adjacentField(attack_coords)) 
  {
    weapon = getRandomWeapon();
  }
  else 
  {
    weapon = getRandomRangedWeapon();
  }

  if (weapon == nullptr) 
  {
    return false;
  }

  if (Command::Errors::NO_ERROR == weapon->attackTarget(this, fields[attack_coords[0]][attack_coords[1]], room, players)) 
  {
    return true;
  }
  return false;
}

///---------------------------------------------------------------------------------------------------------------------
Weapon* Character::getRandomWeapon() 
{
  int options = weapons_.size();

  if (options == 0) 
  {
    return nullptr;
  }

  int rand_number = Oop::Random::getInstance().getRandomNumber(options);
  Item *item = weapons_[rand_number - 1];
  Weapon* weapon = dynamic_cast<Weapon*>(item);
  return weapon;
}

///---------------------------------------------------------------------------------------------------------------------
Weapon* Character::getRandomRangedWeapon() 
{

  //count options
  int options = 0;
  for (Item *i : weapons_) 
  {
    Item *item = i;
    Weapon* weapon = dynamic_cast<Weapon*>(item);
    if (weapon->getAttackType() == Weapon::AttackType::RANGED)
    {
      options++;
    }
  }
  
  if (options == 0) 
  {
    return nullptr;
  }

  //get random number
  int rand_number = Oop::Random::getInstance().getRandomNumber(options);
  int count = 0;

  //find weapon
  for (Item *i : weapons_) 
  {
    Item *item = i;
    Weapon* weapon = dynamic_cast<Weapon*>(item);
    if (weapon->getAttackType() == Weapon::AttackType::RANGED)
    {
      count++;
      if (count == rand_number) 
      {
        return weapon;
      }
    }
  }

  return nullptr;
} 

///---------------------------------------------------------------------------------------------------------------------
int Character::findTarget(std::vector<Player *> players) 
{
  std::vector<int> distances;

  for (Player *player : players) 
  {
    int distance;
    if (player->getCharacter()->isAlive()) 
    {
      distance = countDistance(player);
    }
    else 
    {
      distance = 200;
    }
    distances.push_back(distance);
  }

  int min_dist = 100;
  std::vector<int> indexes_dist;

  // Find minimum distance
  for (std::size_t i = 0; i < distances.size(); i++) 
  {
    if (min_dist > distances[i]) 
    {
      min_dist = distances[i];
    }
  }

  // Find indices with minimum distance
  for (std::size_t i = 0; i < distances.size(); i++) 
  {
    if (min_dist == distances[i]) 
    {
      indexes_dist.push_back(i);
    }
  }

  // If no duplicates
  if (indexes_dist.size() == 1) 
  {
    return indexes_dist[0];
  }

  std::vector<int> indexes_hp;
  std::vector<int> hps;

  // Get HP of characters with the same distance
  for (std::size_t i : indexes_dist) 
  {
    int hp = players[i]->getCharacter()->getHP();
    hps.push_back(hp);
    indexes_hp.push_back(i);
  }

  int min_hp = 100;
  std::vector<int> indexes_min_hps;

  // Find minimum HP
  for (std::size_t i = 0; i < hps.size(); i++) 
  {
    if (min_hp > hps[i] && hps[i] != 0) 
    {
      min_hp = hps[i];
    }
  }

  // Find indices with minimum HP
  for (std::size_t i = 0; i < hps.size(); i++) 
  {
    if (min_hp == hps[i]) 
    {
      indexes_min_hps.push_back(indexes_hp[i]);
    }
  }

  // Return index of the character with minimum HP
  if (indexes_min_hps.size() == 1) 
  {
    return indexes_min_hps[0];
  }

  // Find the character in the clockwise manner, return the index
  std::vector<std::vector<int>> coordinates_characters;
  for (int i : indexes_min_hps) 
  {
    std::vector<int> coor = players[i]->getCharacter()->getCoordinates();
    coordinates_characters.push_back(coor);
  }

  int earlier = earlierClockwise(coordinates_characters);
  return indexes_min_hps[earlier];
}

///---------------------------------------------------------------------------------------------------------------------
int Character::earlierClockwise(std::vector<std::vector<int>> coordinates) 
{
  std::vector<std::vector<int>> derections = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1},
  {-2,0}, {-2,1}, {-2,2}, {-1,2}, {0,2}, {1,2}, {2,2}, {2,1}, {2,0}, {2,-1}, {2,-2}, {1,-2}, {0,-2}, {-1,-2}, {-2,-2}, {-2,-1}};

  for (auto positions : derections) 
  {
    std::vector<int> new_derections (2);
    new_derections[0] = coordinates_[0] + positions[0];
    new_derections[1] = coordinates_[1] + positions[1];

    for (std::size_t i = 0; i < coordinates.size(); i++) 
    {
      if (coordinates[i] == new_derections) 
      {
        return i;
      }
    }
  }
  return 0;
}

///---------------------------------------------------------------------------------------------------------------------
bool Character::adjacentField(std::vector<int> coordinates) 
{
  int row_dist = abs(coordinates_[0] - coordinates[0]);
  int column_dist = abs(coordinates_[1] - coordinates[1]);

  return (row_dist < 2 && column_dist < 2);
}

///---------------------------------------------------------------------------------------------------------------------
int Character::countDistance(Player *player) 
{
  std::vector <int> coordinates_player = player->getCharacter()->getCoordinates();

  int distance = abs(coordinates_[0] - coordinates_player[0]) + abs(coordinates_[1] - coordinates_player[1]);
  return distance;
}

///---------------------------------------------------------------------------------------------------------------------
void Character::move(Room *room) 
{
  std::vector<int> position(2);

  position = getCoordinates();

  int possible_fields = room->countPossibleFields(position);
  int random_result = Oop::Random::getInstance().getRandomNumber(possible_fields);

  std::vector<int> random_position(2);
  std::vector<int> new_position(2);
  random_position = room->identifyRandomPosition(random_result, position);

  std::vector<std::vector<Field *>> &fields = room->getFields();
  if (fields[random_position[0]][random_position[1]]->getEntity() == nullptr) 
  {
    new_position = random_position;
  }  
  else 
  {
    new_position = room->findEmptySpot(random_position[0], random_position[1]);
  }

  this->setCoordinates(new_position[0], new_position[1]);
  fields[new_position[0]][new_position[1]]->setEntity(this);
  fields[position[0]][position[1]]->delEntity();

  std::cout << "\n" << this->getFullName() << " " << this->getId()<< " [" << this->getFullName()[0] 
            << this->getId() << "] moved to (" << new_position[0] + 1 << "," << new_position[1] + 1 << ").\n";
}

///---------------------------------------------------------------------------------------------------------------------
Door::Door(int next_room) 
{
  type_ = Entity::EntityType::DOOR;
  id_ = next_room;
  locked_ = true;

  next_room_id_ = next_room;
  if (next_room_id_ == 0) 
  {
    next_room_ = nullptr;
  }
}

///---------------------------------------------------------------------------------------------------------------------
bool Door::doorGetLocked() 
{
  return locked_;
}

///---------------------------------------------------------------------------------------------------------------------
Room *Door::doorGetRoom() 
{
  return next_room_;
}

///---------------------------------------------------------------------------------------------------------------------
Chest::Chest(std::vector<std::string> items, int value_unlock) 
{
  type_ = Entity::EntityType::CHEST;
  id_ = value_unlock;

  for (std::size_t i = 0; i < items.size(); i += 2) 
  {
    std::string item = items[i];
    int amount = stoi(items[i + 1]);
    Item *new_item = nullptr;

    if (item == "NHEP" || item == "GHEP" || item == "SHEP") \
    {
      new_item = new HealthPotions(item, amount);
    }
    else if (item == "FIRS" || item == "CORS" || item == "FORS" || item == "ACRS") 
    {
      new_item = new ResistPotions(item, amount);
    }
    else if (item == "LARM" || item == "BPLT" || item == "CHML" || item == "PARM") 
    {
      new_item = new Armor(item, amount);
    }
    else if (item == "ARRW" || item == "BOLT") 
    {
      new_item = new Ammunition(item, amount);
    } 
    else if (item == "DAGG" || item == "MACE" || item == "WARH" || item == "HAXE" ||
          item == "GAXE" || item == "RAPI" || item == "SSWD" || item == "LSWD" ||
          item == "GSWD" || item == "SBOW" || item == "LBOW" || item == "LCRS" ||
          item == "HCRS" || item == "QFIR" || item == "QCLD" || item == "QACD" ||
          item == "QFRC") 
    {
      new_item = new Weapon(item, amount);
    }

    loot_.push_back(new_item);
  }
}

///---------------------------------------------------------------------------------------------------------------------
Chest::~Chest() 
{
  for (auto& item : loot_) 
  {
    delete item;
  }
  loot_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
std::vector<Item *>& Chest::getLoot() 
{
  return loot_;
}

///---------------------------------------------------------------------------------------------------------------------
void Chest::clearInventory() 
{
  loot_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
void Entity::setCoordinates(int x, int y)
{
  coordinates_.clear();
  coordinates_.push_back(x);
  coordinates_.push_back(y);
}

///---------------------------------------------------------------------------------------------------------------------
std::vector<int> Entity::getCoordinates() const
{
  return coordinates_;
}

///---------------------------------------------------------------------------------------------------------------------
std::string Character::getFullName() const
{
  std::string full_name;
  switch (char_type_)
  {
    case CharacterType::BARBARIAN:
      full_name = "Barbarian";
      break;
    case CharacterType::WIZARD:
      full_name = "Wizard";
      break;
    case CharacterType::ROGUE:
      full_name = "Rogue";
      break;
    case CharacterType::ZOMBIE:
      full_name = "Zombie";
      break;
    case CharacterType::GOBLIN:
      full_name = "Goblin";
      break;
    case CharacterType::LICH:
      full_name = "Lich";
      break;
  }
  return full_name;
}

///---------------------------------------------------------------------------------------------------------------------
void DeathLocation::clearInventory() 
{
  loot_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
DeathLocation::~DeathLocation()
{
  for (auto& item : loot_) 
  {
    delete item;
  }
  loot_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
std::vector<Item *>& DeathLocation::getLoot() 
{
  return loot_;
}

///---------------------------------------------------------------------------------------------------------------------
void Door::open() 
{
  locked_ = false;
}

///---------------------------------------------------------------------------------------------------------------------
void Door::setPointer(Room *next_room) 
{
  next_room_ = next_room;
}
