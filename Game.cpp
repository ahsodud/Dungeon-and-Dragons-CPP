///---------------------------------------------------------------------------------------------------------------------
/// Game.cpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include <algorithm>
#include <iomanip>
#include <ctype.h>

#include "Game.hpp"

Game::Game() : map_(nullptr) {};

///---------------------------------------------------------------------------------------------------------------------
Game::Game(char* dungeon_file, char* story_file) 
{
  map_ = new Map(dungeon_file);
  rooms_ = map_->getTotalRooms();
  completed_rooms_ = 0;

  parseStoryFile(story_file);
  players_.reserve(3);

  printingMap = true;
  printingStory = true;

  printMessage("N_INTRO");
};

///---------------------------------------------------------------------------------------------------------------------
Game::~Game()
{
  delete map_;
  
  for (Player* player : players_) 
  {
    delete player;
  }
  players_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
int Game::rollDice(int dice_amount, int dice_upper_bound)
{
  int total_value = 0;

  for (int i = 0; i < dice_amount; i++)
    total_value = total_value + Oop::Random::getInstance().getRandomNumber(dice_upper_bound);

  std::cout << "[Dice Roll] " << dice_amount << " d" << dice_upper_bound;
  std::cout << " resulting in a total value of " << total_value << "." << std::endl;
  std::cout << std::endl;

  return total_value;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::parseStoryFile(char* story_file) 
{
  std::ifstream file{story_file};
  std::vector<std::string> rows;

  if (file.is_open()) 
  {
    rows = Utils::readRows(file);
  }

  rows.erase(rows.begin()); //erase the first element

  std::map<std::string, std::string> messages;
  for (std::string row : rows) 
  {
    std::string string_parts[2];
    int current_part = 0;

    for (char c : row) 
    {
     if (c != ':') 
     {
      string_parts[current_part] += c;
     }
     else 
     {
      current_part++;
     } 
    }

    messages[string_parts[0]] = string_parts[1];
  }

  messages_ = messages;
};

///---------------------------------------------------------------------------------------------------------------------
bool Game::isValidConfigStory(char* config_path) 
{
  std::ifstream file{config_path};

  if (file.is_open())
  {
    std::vector<std::string> rows = Utils::readRows(file);
    if (rows[0] == "STORY")
    {
      return true;
    }
  }

  return false;
};

///---------------------------------------------------------------------------------------------------------------------
void Game::printMessage(std::string key) 
{
  std::string message = messages_[key];
  std::string sign;

  if (key[0] == 'N') 
  {
    sign = "** ";
  } else 
  {
    sign = "!! ";
  }

  int new_lines_end = 0;
  int new_lines_start = 0;

  int length = message.size() - 1;
  while (length >= 0 && message[length] == ';') 
  {
    new_lines_end++;
    length--;
  }

  int index = 0;
  while (message[index] == ';') 
  {
    new_lines_start++;
    index++;
  }
  if (new_lines_start == 0) 
  {
    std::cout << sign;
  }

  for (int position = 0; position <= length; position++) 
  {
    if (message[position] == ';') 
    {

      if (position + 1 <= length && message[position + 1] == ';') 
      {
        std::cout << "\n\n" << sign;
        position++;
      }
      else 
      {
        std::cout << "\n" << sign;
      }
    } 
    else 
    {
      std::cout << message[position];
    }
  }

  // Print new lines at the end
  for (int i = 0; i < new_lines_end; i++) {
    std::cout << '\n';
  }
}

///---------------------------------------------------------------------------------------------------------------------
bool Game::isRunning() 
{
  return !(phase_ == Phase::END);
};

///---------------------------------------------------------------------------------------------------------------------
bool Game::isValidConfigDungeon(char* config_path) 
{
  std::ifstream file{config_path};

  if (file.is_open())
  {
    std::vector<std::string> rows = Utils::readRows(file);
    if (rows[0] == "DUNGEON")
    {
      return true;
    }
  }

  return false;
};

///---------------------------------------------------------------------------------------------------------------------
int Game::start() 
{
  std::string players_string = "";
  int players = 0;
  std::string character = "";
  bool validInput = false;
  std::vector<std::string> usedNames; // Vector to store used names
  std::vector<int> classCount(3, 0); // Vector to store the count of each class
  std::cout << "How many players want to join the adventure? (1 to 3)\n> ";

  while (!validInput) 
  {
    std::getline(std::cin, players_string);
    CommandLine::removeWhitespacesAtEnds(players_string);

    // Convert to uppercase for case-insensitive comparison
    for (char &c : players_string)
    {
      c = std::toupper(c);
    }
    if (players_string == "QUIT" || players_string == "") 
    {
      return 1; // Exit the function
    }

    try 
    {
      players = std::stoi(players_string);
      if (players >= 1 && players <= 3) 
      {
        validInput = true;
      } 
      else 
      {
        std::cout << "Please enter a number of players between 1 and 3.\n> ";
      }
    }
    catch (std::invalid_argument &e) 
    {
      std::cout << "Please enter a number of players between 1 and 3.\n> ";
    }
    catch (std::out_of_range &e) 
    {
      std::cout << "Please enter a number of players between 1 and 3.\n> ";
    }
  }

  for(int id = 1; id <= players; id++)
  {
    std::string name;
    bool validName = false;
    
    std::cout << "\nPlayer " << id << " what do you wish to be called? (max length 10 characters)\n> ";
    while (!validName) 
    {
      std::getline(std::cin, name);
      
      if (name.length() > 10) 
      {
        std::cout << "Please enter a unique name with not more than 10 characters.\n> ";
      } 
      else if (std::find(usedNames.begin(), usedNames.end(), name) == usedNames.end()) 
      {
        usedNames.push_back(name); // Add the name to used names
        validName = true;
      } 
      else 
      {
        std::cout << "Please enter a unique name with not more than 10 characters.\n> ";
      }
    }
    
    auto player = std::make_unique<Player>(name, id);
    std::cout << player->getName() << ", please choose a player type:\n";

    // Print available classes based on previous selections
    std::cout << "  [W] Wizard     " << (classCount[0] == 0 ? "0/1" : "1/1") << "\n";
    std::cout << "  [B] Barbarian  " << (classCount[1] == 0 ? "0/1" : "1/1") << "\n";
    std::cout << "  [R] Rogue      " << (classCount[2] == 0 ? "0/1" : "1/1") << "\n> ";

    bool validClass = false;
    while (!validClass) 
    {
      std::getline(std::cin, character);
      CommandLine::removeWhitespacesAtEnds(character);
      
      for (char &c : character)
        c = std::toupper(c);

      if (character == "QUIT" || character == "") 
      {
        return 1; // Exit the function
      }

      // Check if the chosen class is available
      if ((character == "W" && classCount[0] == 0) || (character == "B" && classCount[1] == 0) || (character == "R" && classCount[2] == 0))
      {
        validClass = true;
      } 
      else if (character == "W" || character == "B" || character == "R") 
      {
        std::cout << "This player type is no longer available. Please choose a different player type.\n> ";
      } 
      else 
      {
        std::cout << "Please enter a letter representing your desired player type (W, B, or R).\n> ";
      }
    }

    player->setClass(character[0]);
    addPlayer(player.release());
    
    // Update the class count
    if (character == "W")
    {
      classCount[0]++;
    }
    else if (character == "B")
    {
      classCount[1]++;
    }
    else if (character == "R")
    {
      classCount[2]++;
    }
  }

  std::cout << "\n-- Players --------------------------------------\n";
  int id = 1;
  std::for_each(players_.begin(), players_.end(), [&id](const Player* player) {
      std::cout << "  Player " << id++ << ": " << *player << "\n";
  });

  std::cout << std::endl;

  actions_ = 0;
  actions_in_current_phase_ = 0;
  phase_ = Phase::PLAYER;

  current_room_ = map_->getFirstRoom();
  enterRoom(current_room_);

  return 0;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::deployPlayers(int door_id)
{
  int columns = current_room_->getColumns();
  int rows = current_room_->getRows();
  std::vector<std::vector<Field*>>& fields = current_room_->getFields();

  int door_row;
  int door_column;

  for (int row = 0; row < rows; row++) 
  {
    for (int column = 0; column < columns; column++) 
    {
      if (fields[row][column]->getEntity() != nullptr) 
      {
        if (fields[row][column]->getEntity()->getEntityType() == Entity::EntityType::DOOR && fields[row][column]->getEntity()->getId() == door_id) 
        {
          door_row = row;
          door_column = column;
        }
      }
    }
  }

  for (Player* player : players_)
  {
    if (player->getCharacter()->isAlive()) 
    {
      std::vector<int> coordinates = current_room_->findEmptySpot(door_row, door_column);
      player->getCharacter()->setCoordinates(coordinates[0],coordinates[1]);
      fields[coordinates[0]][coordinates[1]]->setEntity(player->getCharacter());
    }
  }

  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::resetValues() 
{
  actions_in_current_phase_ = -1;
  phase_ = Phase::PLAYER;
  action_ = true;

  for (auto& player : players_) 
  {
    player->getCharacter()->setResistance(Item::DamageType::NONE);
  }
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::printRoom() 
{
  //print message
  if (current_room_->enteredFirst()) 
  {
    std::string signs = current_room_->getEnemiesSigns(); 

    if (printingStory) 
    {
      std::string id = std::to_string(current_room_->getId());
      std::string room_key = "N_ROOM_";
      room_key.append(id);

      Game::printMessage(room_key);
      printEnemiesMessages(signs);
    }
    enemies_met_.append(signs);
    current_room_->SwitchEnteredFirst();
  }

  //print header
  std::cout << "\n-- ROOM " << current_room_->getId() << " (" << completed_rooms_ << "/" << rooms_ << " completed) --------------------\n\n";

  //print the map
  if (printingMap) {
    current_room_->printMap();
  }
  
  if (!allEnemiesDead()) {
    current_room_->printEnemies();
  }
  else {
    std::cout << "\n";
  }
  return;
};

///---------------------------------------------------------------------------------------------------------------------
void Game::storyCommand() 
{
  if (printingStory) 
  {
    printingStory = false;
  }
  else 
  {
    printingStory = true;
  }

  nextMove();
  return;
};

///---------------------------------------------------------------------------------------------------------------------
void Game::mapCommand() 
{
  if (printingMap) 
  {
    printingMap = false;
  }
  else 
  {
    printingMap = true;
    current_room_->printMap();
  }

  nextMove();
  return;
};

///---------------------------------------------------------------------------------------------------------------------
void Game::posCommand()
{
  for(auto player: players_)
  {
    if (player->getCharacter()->isAlive()) 
    {
     std::cout << *player << " on (" << player->getCharacter()->getCoordinates()[0] + 1 << "," << player->getCharacter()->getCoordinates()[1] + 1 << ")\n";
    }
  }

  auto enem = current_room_->getEnemies();
  std::sort(enem.begin(), enem.end(), [](const auto* a, const auto* b) {
    if (a->getFullName() != b->getFullName()) 
    {
      return a->getFullName() < b->getFullName();
    } 
    else 
    {
      return a->getId() < b->getId();
    }
    });


  for(auto enemies: enem)
  if (enemies->isAlive()) {
    {
      std::cout << enemies->getFullName() << " " << enemies->getId() << " [" << enemies->getFullName()[0] << enemies->getId() << "] " << "on (" << enemies->getCoordinates()[0] + 1 << "," << enemies->getCoordinates()[1] + 1 << ")\n";
    }
  }
  
  nextMove();
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::moveCommand(std::vector<std::string> param) 
{
  if (param[0].length() != 1 || (param[0][0] != 'B' && param[0][0] != 'R' && param[0][0] != 'W')) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  std::vector<std::string> coordinates;
  int count_comas = 0;
  for (char c : param[1]) 
  {
    if (c == ',') 
    {
      count_comas++;
    }
  }
  CommandLine::stringToVector(param[1], coordinates, ',');
  if (coordinates.size() != 2 || count_comas != 1) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  for (std::string arg : coordinates) 
  {
    for (char c : arg) 
    {
      if (!isdigit(c) && c != '-') 
      {
        printMessage("E_INVALID_PARAM");
        return;
      }
    }
  }
    
  int row, column;

  try 
  {
    row = stoi(coordinates[0]);
    column = stoi(coordinates[1]);
  }
  catch (std::invalid_argument &e) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  row--;
  column--;
  
  char char_type = param[0][0];

  bool player_found = false;
  Character *character = nullptr;
  Player *f_player = nullptr;

  auto it = std::find_if(players_.begin(), players_.end(), [char_type](Player *player) {
    return player->getCharacter()->isAlive() && char_type == player->getClass()[0];
  });

  if (it != players_.end()) 
  {
    player_found = true;
    character = (*it)->getCharacter();
    f_player = *it;
  } 
  else 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }


  if (row < 0 || column < 0 || row >= current_room_->getRows() || column >= current_room_->getColumns()) 
  {
    printMessage("E_INVALID_POSITION");
    return;
  }

  std::vector<int> current_coordinates = character->getCoordinates();
  int dif_row = abs(current_coordinates[0] - row);
  int dif_column = abs(current_coordinates[1] - column);

  if (dif_row > 1 || dif_column > 1 || (dif_row == 0 && dif_column == 0)) 
  {
    printMessage("E_INVALID_POSITION");
    return;
  }
  
  std::vector<std::vector<Field *>>& fields = current_room_->getFields();
  if (fields[row][column]->getEntity() == nullptr) 
  {
    fields[row][column]->setEntity(character);
    fields[current_coordinates[0]][current_coordinates[1]]->delEntity();
    character->setCoordinates(row, column);

    std::cout << character->getFullName() << " [" << character->getFullName()[0] << "] \""
    << f_player->getName() << "\" moved to (" << row + 1 << "," << column + 1 << ").\n";

    character->setCoordinates(row, column);
    action_ = true;
    actions_++;
    nextMove();
    return;
  }
  else 
  {
    if (fields[row][column]->getEntity()->getEntityType() == Entity::EntityType::DOOR) 
    {
      Door* door = dynamic_cast<Door*>(fields[row][column]->getEntity());
      if (door->doorGetLocked()) 
      {
        printMessage("E_MOVE_LOCKED_DOOR");
        return;
      }
      else 
      {
        character->setCoordinates(row, column);

        std::cout << character->getFullName() << " [" << character->getFullName()[0] << "] \""
        << f_player->getName() << "\" moved to (" << row + 1 << "," << column + 1 << ").\n";
        character->setCoordinates(row, column);

        actions_++;
        enterRoom(door->doorGetRoom());
        return;
      }
    }
    else 
    {
      printMessage("E_INVALID_POSITION");
      return;
    }
  }

  return;
}
///---------------------------------------------------------------------------------------------------------------------
void Game::useCommand(std::vector<std::string> param) 
{
  if (param[0].length() != 1 || (param[0][0] != 'B' && param[0][0] != 'R' && param[0][0] != 'W')) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }
  
  char char_type = param[0][0];

  bool player_found = false;
  Character *character = nullptr;
  Player *f_player = nullptr;

  auto it = std::find_if(players_.begin(), players_.end(), [char_type](Player *player) {
    return player->getCharacter()->isAlive() && char_type == player->getClass()[0];
  });

  //do not delete, here for a reason
  if (!(param[1] == "NHEP" || param[1] == "GHEP" || param[1] == "SHEP" ||
     param[1] == "FIRS" || param[1] == "CORS" || param[1] == "FORS" || param[1] == "ACRS" ||
     param[1] == "LARM" || param[1] == "BPLT" || param[1] == "CHML" || param[1] == "PARM" ||
     param[1] == "DAGG" || param[1] == "MACE" || param[1] == "WARH" || param[1] == "HAXE" ||
     param[1] == "GAXE" || param[1] == "RAPI" || param[1] == "SSWD" || param[1] == "LSWD" ||
     param[1] == "GSWD" || param[1] == "SBOW" || param[1] == "LBOW" || param[1] == "LCRS" ||
     param[1] == "HCRS" || param[1] == "QFIR" || param[1] == "QCLD" || param[1] == "QACD" ||
     param[1] == "QFRC")) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  } 

  if (it != players_.end()) 
  {
    player_found = true;
    character = (*it)->getCharacter();
    f_player = *it;
  } 
  else 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  if (!(param[1] == "NHEP" || param[1] == "GHEP" || param[1] == "SHEP" ||
     param[1] == "FIRS" || param[1] == "CORS" || param[1] == "FORS" || param[1] == "ACRS" ||
     param[1] == "LARM" || param[1] == "BPLT" || param[1] == "CHML" || param[1] == "PARM" ||
     param[1] == "DAGG" || param[1] == "MACE" || param[1] == "WARH" || param[1] == "HAXE" ||
     param[1] == "GAXE" || param[1] == "RAPI" || param[1] == "SSWD" || param[1] == "LSWD" ||
     param[1] == "GSWD" || param[1] == "SBOW" || param[1] == "LBOW" || param[1] == "LCRS" ||
     param[1] == "HCRS" || param[1] == "QFIR" || param[1] == "QCLD" || param[1] == "QACD" ||
     param[1] == "QFRC")) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  } 

  if (!player_found) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  if (param[1] == "NHEP" || param[1] == "GHEP" || param[1] == "SHEP") 
  {
    useHealthPotion(f_player, param[1]);
  }
  else if (param[1] == "FIRS" || param[1] == "CORS" || param[1] == "FORS" || param[1] == "ACRS") 
  {
    useResistancePotion(f_player, param[1]);
  }
  else if (param[1] == "LARM" || param[1] == "BPLT" || param[1] == "CHML" || param[1] == "PARM") 
  {
    useArmor(f_player, param[1]);
  } 
  else if (param[1] == "DAGG" || param[1] == "MACE" || param[1] == "WARH" || param[1] == "HAXE" ||
         param[1] == "GAXE" || param[1] == "RAPI" || param[1] == "SSWD" || param[1] == "LSWD" ||
         param[1] == "GSWD" || param[1] == "SBOW" || param[1] == "LBOW" || param[1] == "LCRS" ||
         param[1] == "HCRS" || param[1] == "QFIR" || param[1] == "QCLD" || param[1] == "QACD" ||
         param[1] == "QFRC") 
  {
    useWeapon(f_player, param[1]);
  }

  if (action_)
    nextMove();
  return;
} 

///---------------------------------------------------------------------------------------------------------------------
bool Game::findItemByAbbr(std::vector<Item> vector, std::string abbr) 
{
  for (auto& item : vector) 
  {
    if (item.getAbbreviation() == abbr) 
    {
      return true;
    }
  }
  return false;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::useHealthPotion(Player* player, std::string abbr) 
{
  std::vector<Item *> inventory = player->getCharacter()->getInventory();
  bool item_found = false;
  Item* f_item;

  int size = inventory.size();

  for (int i = 0; i < size; i++) 
  {
    if (inventory[i]->getAbbreviation() == abbr) 
    {
      f_item = inventory[i];
      item_found = true;
    }
  }

  if (!item_found) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  HealthPotions *health_potion = dynamic_cast<HealthPotions *>(f_item);
  Character *character = player->getCharacter();
  
  std::cout << player->getClass() << " [" << player->getClass()[0] << "] \""
          << player->getName() << "\" consumed \"" << health_potion->getName() << "\".\n";

  int restored_helath = health_potion->restoreHealth(character);

  std::cout << player->getClass() << " [" << player->getClass()[0] << "] \""
            << player->getName() << "\" regenerates " << restored_helath << " health.\n";

  int amount = health_potion->getAmount();

  if (amount == 1) 
  {
    character->eraseItem(health_potion);
    delete health_potion;
  }
  else 
  {
    health_potion->setAmount(-1);
  }
  actions_++;
  action_ = true;
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::useResistancePotion(Player* player, std::string abbr) 
{
  std::vector<Item *> inventory = player->getCharacter()->getInventory();
  bool item_found = false;
  Item* f_item;

  int size = inventory.size();

  for (int i = 0; i < size; i++) 
  {
    if (inventory[i]->getAbbreviation() == abbr) 
    {
      f_item = inventory[i];
      item_found = true;
    }
  }

  if (!item_found) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  ResistPotions *r_potion = dynamic_cast<ResistPotions *>(f_item);
  Character *character = player->getCharacter();

  Item::DamageType type = r_potion->getResistType();
  std::string damage_type;

  switch (type)
  {
  case Item::DamageType::ACID:
    damage_type = "Acid";
    break;

  case Item::DamageType::COLD:
    damage_type = "Cold";
    break;
  
  case Item::DamageType::FIRE:
    damage_type = "Fire";
    break;
  
  case Item::DamageType::FORCE:
    damage_type = "Force";
    break;

  case Item::DamageType::PHYSICAL:
    damage_type = "Physical";
    break;
  
  default:
    break;
  }


  r_potion->applyResist(character);
  std::cout << player->getClass() << " [" << player->getClass()[0] << "] \"" << player->getName()
            << "\" consumed \"" << r_potion->getName() << "\".\n";
  std::cout << player->getClass() << " [" << player->getClass()[0] << "] \"" << player->getName()
            << "\" is now resistant to \"" << damage_type << "\" until leaving the room.\n";

  int amount = r_potion->getAmount();

  if (amount == 1) 
  {
    character->eraseItem(r_potion);
    delete r_potion;
  }
  else 
  {
    r_potion->setAmount(-1);
  }
  actions_++;
  action_ = true;
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::useArmor(Player* player, std::string abbr) 
{
  //remove the eq armor
  Item *eq_armor = player->getCharacter()->getEquippedArmor();
  Character *character = player->getCharacter();

  if (eq_armor != nullptr && eq_armor->getAbbreviation() == abbr) 
  {
    // Ensure eq_armor is actually an Armor instance
    Armor *armor = dynamic_cast<Armor*>(eq_armor);
    if (armor != nullptr) {
      std::vector<Item *> armors;
      armors.push_back(eq_armor);
      character->lootArmor(armors);
      character->setEquippedArmor(nullptr);

      if(abbr == "LARM")
      {
        character->AdjustArmorValue(-character->getVitality() + 1);
        character->AdjustArmorValue(-armor->getArmorValue());
      }
      else if(abbr == "BPLT")
      {
        character->AdjustArmorValue(-fmin(character->getVitality(),2));
        character->AdjustArmorValue(-armor->getArmorValue());
      }
      else character->AdjustArmorValue(-armor->getArmorValue());

      actions_++;
      action_ = true;
      return;
    }
  }

  //find the armor
  std::vector<Item *> armors = player->getCharacter()->getArmor();
  bool item_found = false;
  Item *f_item;
  int index = 0;

  for (std::size_t i = 0; i < armors.size(); i++) {
    if (armors[i]->getAbbreviation() == abbr) {
      item_found = true;
      f_item = armors[i];
      index = i;
      break;
    }
  }
  
  if (!item_found) {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  //remove and loot eq armor
  if (eq_armor != nullptr) {
    if (Character::findItem(armors, eq_armor)) {
      Character::addFoundItem(armors, eq_armor);
      delete eq_armor;
    }
    else {
      character->addArmor(eq_armor);
    }
  }

  //set and delete armor from inventory
  int amount = f_item->getAmount();
  if (amount > 1) {
    armors[index]->setAmount(-1);
    Armor* new_armor = new Armor(abbr, 1);
    character->calculateArmor(new_armor->getArmorValue());
    character->setEquippedArmor(new_armor); 
  }
  else {
    Armor* armor = dynamic_cast<Armor*>(f_item);
    if (armor != nullptr) {
      character->setEquippedArmor(armor);
      armor->applyArmor(character);
      character->eraseArmor(f_item);
    }
  }
  actions_++;
  action_ = true;
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::useWeapon(Player* player, std::string abbr) 
{
  //remove the eq weapom
  Item *eq_weapon = player->getCharacter()->getEquippedWeapon();
  Character *character = player->getCharacter();

  if (eq_weapon != nullptr && eq_weapon->getAbbreviation() == abbr) 
  {
    std::vector <Item *> weapons;
    weapons.push_back(eq_weapon);
    character->lootWeapons(weapons);
    character->setEquippedWeapon(nullptr);
    actions_++;
    action_ = true;
    return;
  }

  //find the weapon
  std::vector<Item *> weapons = player->getCharacter()->getWeapons();
  bool item_found = false;
  Item *f_item;
  int index = 0;

  for (std::size_t i = 0; i < weapons.size(); i++) 
  {
    if (weapons[i]->getAbbreviation() == abbr) 
    {
      item_found = true;
      f_item = weapons[i];
      index = i;
      break;
    }
  }
  
  if (!item_found) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  //remove and loot eq weapon
  if (eq_weapon != nullptr) 
  {
    if (Character::findItem(weapons, eq_weapon)) 
    {
      Character::addFoundItem(weapons, eq_weapon);
      delete eq_weapon;
    }
    else 
    {
      character->addWeapon(eq_weapon);
    }
  }

  //set and delete weapon from inventory
  int amount = f_item->getAmount();
  if (amount > 1) 
  {
    weapons[index]->setAmount(-1);
    Item* new_weapon = new Weapon(abbr, 1);
    character->setEquippedWeapon(new_weapon); 
  }
  else 
  {
    character->setEquippedWeapon(f_item);  
    character->eraseWeapon(f_item);
  }
  actions_++;
  action_ = true;
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::enterRoom(Room *room) 
{
  int door_id = 0;

  if (current_room_ == room) 
  {
    door_id = 0;
  }
  else 
  {
    door_id = current_room_->getId();
  }

  if (door_id != 0) 
  {
    current_room_->resetCharacters();
  }

  if (room == nullptr) 
  {
    current_room_->resetCharacters();
    exitDangeon();
    return;
  }

  current_room_ = room;
  deployPlayers(door_id);
  resetValues();

  // Start the player phase
  nextMove();
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::end()
{
    current_room_->resetCharacters();

    printEndGameStatistic();
    printMessage("N_SCORING_FILE");
    std::cout << "> ";
    std::string path;
    std::getline(std::cin, path);
    CommandLine::removeWhitespacesAtEnds(path); 

    // Convert path to lowercase
    std::transform(path.begin(), path.end(), path.begin(), [](unsigned char c){ return std::tolower(c); });

    if (path == "quit" || path.empty()) 
    {
      phase_ = Phase::END;
      return;   
    } 
    else 
    {
      saveData(path);
      phase_ = Phase::END;
      return;
    }
}

///---------------------------------------------------------------------------------------------------------------------
void Game::exitDangeon() 
{
  printMessage("N_FLIGHT");
  end();
}

///---------------------------------------------------------------------------------------------------------------------
void Game::printEndGameStatistic()
{
  std::cout << "-- Players --------------------------------------\n";

  // Sort players_ vector by player IDs
  std::sort(players_.begin(), players_.end(), [](const auto& a, const auto& b) {
      return a->getId() < b->getId();
  });

  // Print surviving players
  for (const auto& player : players_)
  {
    if (player->getCharacter()->isAlive())
    {
      std::cout << "  " << *player << " survived.\n";
    }
  }

  // Print defeated players
  for (const auto& player : players_)
  {
    if (!player->getCharacter()->isAlive())
    {
      std::cout << "  " << *player << ", rest in peace.\n";
    }
  }

  std::cout << "\n-- Statistics -----------------------------------\n";
  std::cout << "  " << completed_rooms_ << " rooms completed\n";
  std::cout << "  " << actions_ << " performed actions\n\n";
}

///---------------------------------------------------------------------------------------------------------------------
void Game::saveData(std::string path)
{
  std::ofstream file(path);
  if (file.is_open()) 
  {
    file << "-- Players --------------------------------------\n";

    // Sort players_ vector by player IDs (assuming getId() returns the player's ID)
    std::sort(players_.begin(), players_.end(), [](const auto& a, const auto& b) {
        return a->getId() < b->getId();
    });

    // Save surviving players
    for (const auto& player : players_)
    {
      if (player->getCharacter()->isAlive())
      {
        file << "  " << *player << " survived.\n";
      }
    }

    // Save defeated players
    for (const auto& player : players_)
    {
      if (!player->getCharacter()->isAlive())
      {
        file << "  " << *player << ", rest in peace.\n";
      }
    }

    file << "\n-- Statistics -----------------------------------\n";
    file << "  " << completed_rooms_ << " rooms completed\n";
    file << "  " << actions_ << " performed actions\n\n";
    
    file.close();
  } 
  else
  {
    printMessage("E_SCORING_FILE_NOT_WRITABLE");
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Game::lootCommand(std::vector<std::string> param) 
{
  if (param[0].length() != 1 || (param[0][0] != 'B' && param[0][0] != 'R' && param[0][0] != 'W')) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  std::vector<std::string> coordinates;
  int count_comas = 0;
  for (char c : param[1]) 
  {
    if (c == ',') 
    {
      count_comas++;
    }
  }
  CommandLine::stringToVector(param[1], coordinates, ',');
  if (coordinates.size() != 2 || count_comas != 1) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  for (std::string arg : coordinates) 
  {
    for (char c : arg) 
    {
      if (!isdigit(c) && c != '-') 
      {
        printMessage("E_INVALID_PARAM");
        return;
      }
    }
  }
   
  int row, column;

  try 
  {
    row = stoi(coordinates[0]);
    column = stoi(coordinates[1]);
  }
  catch (std::invalid_argument &e) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  row--;
  column--;
  
  char char_type = param[0][0];

  bool player_found = false;
  Character *character = nullptr;
  Player *f_player = nullptr;

  auto it = std::find_if(players_.begin(), players_.end(), [&](Player* player) {
      return player->getCharacter()->isAlive() && char_type == player->getClass()[0];
  });

  if (it != players_.end()) 
  {
    player_found = true;
    f_player = *it;
    character = f_player->getCharacter();
  }

  if (!player_found) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  if (row < 0 || column < 0 || row >= current_room_->getRows() || column >= current_room_->getColumns()) 
  {
    printMessage("E_INVALID_POSITION");
    return;
  }

  std::vector<int> current_coordinates = character->getCoordinates();
  int dif_row = abs(current_coordinates[0] - row);
  int dif_column = abs(current_coordinates[1] - column);

  if (dif_row > 1 || dif_column > 1 || (dif_row == 0 && dif_column == 0)) 
  {
    printMessage("E_INVALID_POSITION");
    return;
  }

  std::vector<Item *> armor;
  std::vector<Item *> weapons;
  std::vector<Item *> consumables;

  std::vector<std::vector<Field *>>& fields = current_room_->getFields();
  if (fields[row][column]->getEntity() == nullptr) 
  {
    printMessage("E_INVALID_POSITION");
    return;
  }
  else 
  {
    if (fields[row][column]->getEntity()->getEntityType() == Entity::EntityType::CHEST) 
    {
      Chest* chest = dynamic_cast<Chest*>(fields[row][column]->getEntity());
      int value_unlock = chest->getId();
      int min_value = value_unlock - character->getVitality();

      std::cout << "** To unlock this chest you need to roll at least " << min_value << " to reach the " << value_unlock << " needed.\n"; 
      int dice_result = rollDice(1, 20);

      if (dice_result < min_value) 
      {
        printMessage("N_LOOT_CHEST_LOCKED");
        actions_++;
        action_ = true;
        nextMove();
        return;
      }
      else 
      {
        printMessage("N_LOOT_SUCCESSFUL");
        actions_++;
        
        std::vector<Item *> loot = chest->getLoot();
        
        for (auto& item : loot) 
        {
          if (item->getItemType() == Item::ItemType::ARMOR) 
          {
            armor.push_back(item);
          }
          else if (item->getItemType() == Item::ItemType::WEAPON) 
          {
            weapons.push_back(item);
          }
          else if (item->getItemType() == Item::ItemType::CONSUMABLES) 
          {
            consumables.push_back(item);
          }
        }

        printItems("  Armor: ", armor);
        printItems("  Weapons: ", weapons);
        printItems("  Consumables: ", consumables);
        

        character->lootArmor(armor);
        character->lootConsumables(consumables);
        character->lootWeapons(weapons);

        chest->clearInventory();
        delete(chest);
        fields[row][column]->delEntity();
      }
    }
    
    else if (fields[row][column]->getEntity()->getEntityType() == Entity::EntityType::DEATH_LOCATION)
    {
      DeathLocation* dl = dynamic_cast<DeathLocation*>(fields[row][column]->getEntity());
      printMessage("N_LOOT_SUCCESSFUL");
      actions_++;

      std::vector<Item *> loot = dl->getLoot();
        
      for (auto& item : loot) 
      {
        if (item->getItemType() == Item::ItemType::ARMOR) 
        {
          armor.push_back(item);
        }
        else if (item->getItemType() == Item::ItemType::WEAPON) 
        {
          weapons.push_back(item);
        }
        else if (item->getItemType() == Item::ItemType::CONSUMABLES) 
        {
          consumables.push_back(item);
        }
      }

      printItems("  Armor: ", armor);
      printItems("  Weapons: ", weapons);
      printItems("  Consumables: ", consumables);
        
      character->lootArmor(armor);
      character->lootConsumables(consumables);
      character->lootWeapons(weapons);

      dl->clearInventory();
      delete(dl);
      fields[row][column]->delEntity();
    }
    else 
    {
      printMessage("E_INVALID_POSITION");
      return;
    }
  }
  action_ = true;
  nextMove();
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::playerCommand(std::vector<std::string> parameters)
{
  int temp;
  std::string param = parameters.at(0); 

  for (char &c : param) 
  {
  c = std::toupper(c);
  }

  if (param.length() > 1 ||                     
      (param != "W" && param != "B" && param != "R") || 
      Utils::decimalStringToInt(param, temp)) 
  {  
    printMessage("E_INVALID_PARAM");
    return;
  }

  auto it = std::find_if(players_.begin(), players_.end(), [&param](Player* player) {
      return player->getCharacter()->isAlive() && toupper(player->getClass()[0]) == param[0];
  });

  if (it == players_.end()) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }
  
  std::unique_ptr<Player> player(*it);

  auto character = player->getCharacter();
  int armorValue = character->getArmorValue();
  int currentHP = character->getHP();
  int maxHP = character->getMaxHP();
  int strength = character->getStrength();
  int vitality = character->getVitality();
  auto coordinates = character->getCoordinates();

  std::cout << *player << " on ("  << coordinates[0] + 1 << ","  << coordinates[1] + 1 << ")\n";
  std::cout << "  Armor Value:    " << std::setw(5) << armorValue << std::endl;
  std::cout << "  Current Health: " << std::setw(5) << currentHP << std::endl;
  std::cout << "  Max Health:     " << std::setw(5) << maxHP << std::endl;
  std::cout << "  Strength:       " << std::setw(5) << strength << std::endl;
  std::cout << "  Vitality:       " << std::setw(5) << vitality << std::endl;

  nextMove();
  player.release();
}

///---------------------------------------------------------------------------------------------------------------------
void Game::inventoryCommand(std::vector<std::string> parameters) 
{
  int temp;
  std::string param = parameters.at(0); 

  for (char &c : param) 
  {
  c = std::toupper(c);
  }

  if (param.length() > 1 ||                     
      (param != "W" && param != "B" && param != "R") || 
      Utils::decimalStringToInt(param, temp)) 
  {  
    printMessage("E_INVALID_PARAM");
    return;
  }

  auto it = std::find_if(players_.begin(), players_.end(), [&param](Player* player) {
      return player->getCharacter()->isAlive() && toupper(player->getClass()[0]) == param[0];
  });

  if (it == players_.end()) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  std::unique_ptr<Player> player(*it);

  std::cout << "Inventory " << "\"" << player->getName() << "\"\n";

  std::cout << "  Equipped Armor: ";
  if (player->getCharacter()->getEquippedArmor() == nullptr) 
  {
      std::cout << "[-] None\n";
  } 
  else 
  {
      std::cout << "[" << player->getCharacter()->getEquippedArmor()->getAbbreviation() << "] " << player->getCharacter()->getEquippedArmor()->getName() << "\n";
  }

  std::cout << "  Equipped Weapon: ";
  if (player->getCharacter()->getEquippedWeapon() == nullptr) 
  {
      std::cout << "[-] None\n";
  } 
  else 
  {
      std::cout << "[" << player->getCharacter()->getEquippedWeapon()->getAbbreviation() << "] " << player->getCharacter()->getEquippedWeapon()->getName() << "\n";
  }
  auto armor = player->getCharacter()->getArmor();
  auto weapons = player->getCharacter()->getWeapons();
  auto consumables = player->getCharacter()->getInventory();
  printItems("  Armor: ", armor);
  printItems("  Weapons: ", weapons);
  printItems("  Consumables: ", consumables);

  nextMove();
  player.release();
}

///---------------------------------------------------------------------------------------------------------------------
void Game::printItems(const std::string& header, std::vector<Item*>& items)
{
  if (!items.empty()) 
  {
    std::cout << header;
    std::sort(items.begin(), items.end(), [](const Item* a, const Item* b) {
        return a->getAbbreviation() < b->getAbbreviation();
    });

    for (size_t i = 0; i < items.size(); ++i) 
    {
      std::cout << *items[i]; // operator<< is overloaded for Item
      if (i != items.size() - 1) 
      {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Game::helpCommand() 
{
  std::cout << "-- Commands ----------------------------------------\n- help\n     Prints this help text.\n\n";
  std::cout << "- quit\n    Terminates the game.\n\n- story\n    Activates or deactivates the stories of the rooms.\n";
  std::cout << "\n- map\n    Activates or deactivates the map.\n\n- positions\n    Prints the current positions of";
  std::cout << " the players and enemies.\n\n- player <PLAYER_TYPE_ABBREVIATION>\n    Prints player ";
  std::cout << "information of the specific player.\n    <PLAYER_TYPE_ABBREVIATION>: type of the player\n\n";
  std::cout << "- inventory <PLAYER_TYPE_ABBREVIATION>\n    Prints the inventory of the specific player.\n";
  std::cout << "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n\n* move <PLAYER_TYPE_ABBREVIATION> <POSITION>\n";
  std::cout << "    Lets the player move to an adjacent field.\n    <PLAYER_TYPE_ABBREVIATION>: type of the player\n";
  std::cout << "    <POSITION>: field at position: <ROW>,<COLUMN>\n\n* loot <PLAYER_TYPE_ABBREVIATION> <POSITION>\n";
  std::cout << "    Lets the player loot an adjacent chest.\n    <PLAYER_TYPE_ABBREVIATION>: type of the player\n";
  std::cout << "    <POSITION>: field at position: <ROW>,<COLUMN>\n\n";
  std::cout << "* use <PLAYER_TYPE_ABBREVIATION> <ITEM_ABBREVIATION>\n";
  std::cout << "    Lets the player use a potion or equip armor or weapons.\n    <PLAYER_TYPE_ABBREVIATION>: type of the player\n";
  std::cout << "    <ITEM_ABBREVIATION>: abbreviation of an item in the players inventory\n\n";
  std::cout << "* attack <PLAYER_TYPE_ABBREVIATION> <POSITION>\n    Lets the player attack with the equipped weapon on the given position.\n";
  std::cout << "    <PLAYER_TYPE_ABBREVIATION>: type of the player\n    <POSITION>: field at position: <ROW>,<COLUMN>\n";
  std::cout << "\n-- Legend ------------------------------------------\n- display commands\n* action commands (count as actions)\n";
  std::cout << "----------------------------------------------------\n";
  nextMove();
  return;
};

///---------------------------------------------------------------------------------------------------------------------
void Game::enemyPhase() 
{
  printRoom();

  std::vector<Character *> enemies_sorted = current_room_->sortEnemies();
  for (auto& enemy : enemies_sorted) 
  {
    if (allPlayersDead()) 
    {
      nextMove();
      return;
    }

    if (!enemy->attack(current_room_, players_, current_room_->getFields())) 
    {
      enemy->move(current_room_);
    }
  }
    
  nextMove();
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::attackCommand(std::vector<std::string> param) 
{
  if (param[0].length() != 1 || (param[0][0] != 'B' && param[0][0] != 'R' && param[0][0] != 'W')) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  std::vector<std::string> coordinates;
  int count_comas = 0;
  for (char c : param[1]) 
  {
    if (c == ',') 
    {
      count_comas++;
    }
  }
  CommandLine::stringToVector(param[1], coordinates, ',');
  if (coordinates.size() != 2 || count_comas != 1) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  for (std::string arg : coordinates) 
  {
    for (char c : arg) 
    {
      if (!isdigit(c) && c != '-') 
      {
        printMessage("E_INVALID_PARAM");
        return;
      }
    }
  }
    
  int row, column;

  try 
  {
    row = stoi(coordinates[0]);
    column = stoi(coordinates[1]);
  }
  catch (std::invalid_argument &e) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  row--;
  column--;

  char char_type = param[0][0];

  bool player_found = false;
  Character *character;
  Player *f_player;
  for (Player *player : players_) 
  {
    if (player->getCharacter()->isAlive() && char_type == player->getClass()[0]) 
    {
      player_found = true;
      character = player->getCharacter();
      f_player = player;
      break;
    }
  } 

  if (!player_found) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }


  Item *item = character->getEquippedWeapon();
  if (item == nullptr) 
  {
    printMessage("E_ATTACK_NO_WEAPON_EQUIPPED");
    return;
  }

  Weapon* weapon;

  try
  {
    weapon = dynamic_cast<Weapon*>(item);
  }
  catch(std::bad_cast &e)
  {
    printMessage("E_ATTACK_NO_WEAPON_EQUIPPED");
    return;
  }

  if (row < 0 || column < 0 || row >= current_room_->getRows() || column >= current_room_->getColumns()) 
  {
    printMessage("E_INVALID_POSITION");
    return;
  }

  std::vector<int> attack_coords (2);
  attack_coords[0] = row;
  attack_coords[1] = column;

  if (weapon->getAttackType() == Weapon::AttackType::MELEE &&
    !((character->getCharType() == Entity::CharacterType::WIZARD
    || character->getCharType() == Entity::CharacterType::LICH)
    && (weapon->getAbbreviation() == "QFIR" || weapon->getAbbreviation() == "QACD"))) 
  {
    if (!character->adjacentField(attack_coords)) 
    {
      printMessage("E_INVALID_POSITION");
      return;
    }
  }

  std::vector<std::vector<Field *>>& fields = current_room_->getFields();

  Command::Errors error = weapon->attackTarget(character, fields[row][column], current_room_, players_);
  
  switch (error)
  {
  case Command::Errors::INVALID_POSITION:
    printMessage("E_INVALID_POSITION");
    return;
  case Command::Errors::ATTACK_NO_AMMUNITION:
    printMessage("E_ATTACK_NO_AMMUNITION");
    return;
  default:
   break;
  }

  action_ = true;
  actions_++;
  nextMove();
  return;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::playerPhase() 
{
  if (action_) 
  {
    printRoom();
  }
  printMessage("N_PROMPT_MESSAGE");
};

///---------------------------------------------------------------------------------------------------------------------
void Game::nextMove() 
{
  if (allEnemiesDead() && current_room_->getId() == rooms_) 
  {
    printMessage("N_COMPLETION");
    end();
    return;
  }
  else if (allPlayersDead()) 
  {
    printMessage("N_DEFEAT");
    end();
    return;
  }

  //change phases if needed
  if(action_ && phase_ == Phase::PLAYER) 
  {
    actions_in_current_phase_++;

    int amount_players = players_.size();
    if (actions_in_current_phase_ == amount_players && !allEnemiesDead()) 
    {
      actions_in_current_phase_ = 0;
      phase_ = Phase::ENEMY;
    }
  }
  else if (phase_ == Phase::ENEMY) 
  {
    action_ = true;
    phase_ = Phase::PLAYER;
  } 

  //act according to the phase
  if (phase_ == Phase::PLAYER) 
  {
    playerPhase();
    return;
  }
  else if (phase_ == Phase::ENEMY) 
  {
    enemyPhase();
    return;
  }
}

///---------------------------------------------------------------------------------------------------------------------
bool Game::allEnemiesDead() 
{
  std::vector<Character *> enemies = current_room_->getEnemies();
  int count = 0;

  for (Character *enemy : enemies) 
  {
    if (enemy->isAlive()) 
    {
      count++;
    }
  }

  if (count == 0) 
  {
    openDoors();
  }

  current_room_->setAliveEnemies(count);
  return (count == 0);
}

///---------------------------------------------------------------------------------------------------------------------
bool Game::allPlayersDead() 
{
  int count = 0;
  for (Player *player : players_) 
  {
    if (player->getCharacter()->isAlive()) 
    {
      count++;
    }
  }

  active_players_ = count;
  return (count == 0);
}

///---------------------------------------------------------------------------------------------------------------------
void Game::execute(Command command) 
{ 
  action_ = false;

  if (command.getType() == Command::CommandType::INVALID) 
  {
    printMessage("E_UNKNOWN_COMMAND");
    return;
  }

  std::vector <std::string> parameters = command.getParameters();
  int size = parameters.size();

  if (command.getNeededParams() != size) 
  {
    printMessage("E_INVALID_PARAM_COUNT");
    return;
  }

  if (command.getType() == Command::CommandType::HELP) 
  {
    helpCommand();
  } 
  else if (command.getType() == Command::CommandType::STORY) 
  {
    storyCommand();
  }
  else if (command.getType() == Command::CommandType::MAP) 
  {
    mapCommand();
  } 
  else if (command.getType() == Command::CommandType::POSITIONS) 
  {
    posCommand();
  }  
  else if (command.getType() == Command::CommandType::PLAYER) 
  {
    playerCommand(command.getParameters());
  }  
  else if (command.getType() == Command::CommandType::INVENTORY) 
  {
    inventoryCommand(command.getParameters());
  }  
  else if (command.getType() == Command::CommandType::MOVE) 
  {
    moveCommand(command.getParameters());
  }  
  else if (command.getType() == Command::CommandType::LOOT) 
  {
    lootCommand(command.getParameters());
  }
  else if (command.getType() == Command::CommandType::USE) 
  {
    useCommand(command.getParameters());
  }  
  else if (command.getType() == Command::CommandType::ATTACK) 
  {
    attackCommand(command.getParameters());
  }
  else if (command.getType() == Command::CommandType::GIVE) 
  {

    giveCommand(command.getParameters());

  }
  return;
};

void Game::giveCommand(std::vector<std::string> param)
{

  if (param[0].length() != 1 || (param[0][0] != 'B' && param[0][0] != 'R' && param[0][0] != 'W')) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  if (param[1].length() != 1 || (param[1][0] != 'B' && param[1][0] != 'R' && param[1][0] != 'W')) 
  {
    printMessage("E_INVALID_PARAM");
    return;
  }

  if(param[0] == param[1]) std::cout << "error message";

  auto gives = std::find_if(players_.begin(), players_.end(), [&param](Player* player) {
      return player->getCharacter()->isAlive() && toupper(player->getClass()[0]) == param[0][0];
  });

  if (gives == players_.end()) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  auto receive = std::find_if(players_.begin(), players_.end(), [&param](Player* player) {
      return player->getCharacter()->isAlive() && toupper(player->getClass()[0]) == param[1][0];
  });

  if (receive == players_.end()) 
  {
    printMessage("E_ENTITY_OR_ITEM_UNAVAILABLE");
    return;
  }

  Player *giver = *gives;
  Player *receiver = *receive;
  
  bool exists;

  auto weapons_giver = giver->getCharacter()->getWeapons();
  for(auto item: weapons_giver)
  {
    if(item->getAbbreviation() == param[2])
    {
      giver->getCharacter()->eraseWeapon(item);
      exists = true;
      receiver->getCharacter()->addWeapon(item);
    }
  }
  
  auto armor_giver = giver->getCharacter()->getArmor();
  for(auto item: armor_giver)
  {
    if(item->getAbbreviation() == param[2])
    {
      giver->getCharacter()->eraseArmor(item);
      exists = true;
      receiver->getCharacter()->addArmor(item);
    }
  }

  if(!exists) std::cout << "Item not available";



  actions_++;
}

///---------------------------------------------------------------------------------------------------------------------
void Game::addPlayer(Player* player)
{
  players_.push_back(player);
}

///---------------------------------------------------------------------------------------------------------------------
void Game::printEnemiesMessages(std::string signs) 
{
  if (signs.size() == 0) 
  {
    return;
  }

  for (char c : signs) 
  {
    bool already_met = false;
    for (char enemy : enemies_met_) 
    {
      if (c == enemy) 
      {
        already_met = true;
        break;
      }
    }

    if (!already_met) 
    {
      std::string key = "N_ENEMY_";
      key.push_back(c);

      printMessage(key);
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
void Game::openDoors() 
{

  std::vector<std::vector<Field *>> fields = current_room_->getFields();
  int columns = current_room_->getColumns();
  int rows = current_room_->getRows();
  bool doors_were_open = true;

  for (int row = 0; row < rows; row++) 
  {
    for (int column = 0; column < columns; column++) 
    {
      if (fields[row][column]->getEntity() != nullptr && 
          fields[row][column]->getEntity()->getEntityType() == Entity::EntityType::DOOR) 
      {
        Door* door = dynamic_cast<Door*>(fields[row][column]->getEntity());
        if (door->doorGetLocked()) 
        {
          door->open();
          doors_were_open = false;
        }
      }
    }
  }

  if (!doors_were_open) 
  {
    completed_rooms_++;
  }
}
