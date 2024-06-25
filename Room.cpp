///---------------------------------------------------------------------------------------------------------------------
/// Random.cpp
///
/// Authors: Tutors
///---------------------------------------------------------------------------------------------------------------------

#include "Room.hpp"
#include "Field.hpp"
#include "Utils.hpp"
#include "CommandLine.hpp"

#include <iostream>
#include <vector>
#include <string>

///---------------------------------------------------------------------------------------------------------------------
Room::Room(std::string& room_params)
{
  //init delimeters for properly reading from file
  alive_enemies_ = 0;
  entered_first_ = true;
  std::vector<std::string> field_params;
  std::string delimeter_semi = ";";
  std::string delimeter_double = ":";
  std::string delimeter_comma = ",";

  size_t pos = 0;
  std::string token;
  while ((pos = room_params.find(delimeter_semi)) != std::string::npos)
  {
    token = room_params.substr(0, pos);
    field_params.push_back(token);
    room_params.erase(0, pos + delimeter_semi.length());
  }
  field_params.push_back(room_params);

  std::string id_string = field_params[0].substr(0, field_params[0].find(delimeter_double));
  field_params[0].erase(0, field_params[0].find(delimeter_double) + delimeter_double.length());

  std::string columns_string = field_params[0].substr(0, field_params[0].find(delimeter_comma));
  field_params[0].erase(0, field_params[0].find(delimeter_comma) + delimeter_comma.length());

  std::string rows_string = field_params[0];

  Utils::decimalStringToInt(id_string, id_);
  Utils::decimalStringToInt(columns_string, columns_);
  Utils::decimalStringToInt(rows_string, rows_);

  fields_.resize(rows_);
  for (int i = 0; i < rows_; ++i) 
  {
    fields_[i].resize(columns_, nullptr); // Initialize each row with nullptrs
  }

  for (int i = 0; i < rows_; i++)
  {
    for (int j = 0; j < columns_; j++)
    {
      fields_[i][j] = new Field(i + 1, j + 1);
    }
  }

  
  for (std::string parameter : field_params) 
  {
    if (parameter[0] == 'D') 
    {
      std::vector<std::string> door_params;
      std::vector<std::string> door_coordinates;

      CommandLine::stringToVector(parameter, door_params, ':');
      CommandLine::stringToVector(door_params[1], door_coordinates, ',');

      int door_row = stoi(door_coordinates[0]) - 1;
      int door_column = stoi(door_coordinates[1]) - 1;
      int next_room = stoi(door_params[2]);

      Door *new_door = new Door(next_room);
      fields_[door_row][door_column]->setEntity(new_door);
      new_door->setCoordinates(door_row, door_column);
    }
    else if (parameter[0] == 'T') 
    {
      std::vector<std::string> chest_params;
      std::vector<std::string> chest_coordinates;
      std::vector<std::string> chest_items;

      CommandLine::stringToVector(parameter, chest_params, ':');
      CommandLine::stringToVector(chest_params[1], chest_coordinates, ',');
      CommandLine::stringToVector(chest_params[2], chest_items, ',');
      
      int chest_row = stoi(chest_coordinates[0]) - 1;
      int chest_column = stoi(chest_coordinates[1]) - 1;
      int value_unlock = stoi(chest_items[0]);

      chest_items.erase(chest_items.begin()); //erase first element

      Chest *new_chest = new Chest(chest_items, value_unlock);
      fields_[chest_row][chest_column]->setEntity(new_chest);
    }
    else if (parameter[0] == 'Z' || parameter[0] == 'G' || parameter[0] == 'L')
    {
      std::vector<std::string> enemy_params;
      std::vector<std::string> enemy_coordinates;

      CommandLine::stringToVector(parameter, enemy_params, ':');
      CommandLine::stringToVector(enemy_params[1], enemy_coordinates, ',');

      int enemy_row = stoi(enemy_coordinates[0]) - 1;
      int enemy_column = stoi(enemy_coordinates[1]) - 1;
      int enemy_id = stoi(enemy_params[2]);

      Character *new_enemy = new Character(parameter[0], enemy_id);
      new_enemy->setCoordinates(enemy_row, enemy_column);
      fields_[enemy_row][enemy_column]->setEntity(new_enemy);
      enemies_.push_back(new_enemy);
      alive_enemies_++;
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
Room::~Room() 
{
  for (auto& row : fields_) 
  {
    for (auto& field : row) 
    {
      delete field;
    }
    row.clear();
  }
  fields_.clear();

  for (auto enemy : enemies_) 
  {
    delete enemy;
  }
  enemies_.clear();
}

///---------------------------------------------------------------------------------------------------------------------
void Room::initDoorPointers(std::vector<Room *> rooms) 
{
  for (int row = 0; row < rows_; row++) 
  {
    for (int column = 0; column < columns_; column++) 
    {
      if (fields_[row][column]->getEntity() != nullptr && 
      fields_[row][column]->getEntity()->getEntityType() == Entity::EntityType::DOOR) 
      {
        Door* door = dynamic_cast<Door*>(fields_[row][column]->getEntity());
        int id = door->getId();
        door->setPointer(Room::findRoom(id, rooms));
      }
    }
  }
}

///---------------------------------------------------------------------------------------------------------------------
int Room::getId(void) 
{
  return id_;
};

///---------------------------------------------------------------------------------------------------------------------
bool Room::enteredFirst(void)
{
  return entered_first_;
};

///---------------------------------------------------------------------------------------------------------------------
int Room::getColumns()
{
  return columns_;
}

///---------------------------------------------------------------------------------------------------------------------
int Room::getRows()
{
  return rows_;
}

///---------------------------------------------------------------------------------------------------------------------
std::vector<std::vector<Field*>>& Room::getFields()
{
  return fields_;
}

///---------------------------------------------------------------------------------------------------------------------
void Room::printMap(void) 
{
  //print coordinates
  std::cout << "    ";
  for (int column = 0; column < columns_; column++) 
  {
    std::cout << " " << column + 1 << "  ";
  }
  std::cout << "\n";

  //print upper border
  std::cout << "   ";
  for (int column = 0; column < columns_; column++) 
  {
    std::cout << "+---";
  }
  std::cout << "+\n";


  for (int row = 0; row < rows_; row++) 
  {
    //print coordinate
    std::cout << " " << row + 1 << " |";

    //print entity inside the field
    for (int column = 0; column < columns_; column++) 
    {
      Field *current_field = fields_[row][column];
      Entity *current_entity = current_field->getEntity();

      if (current_entity == nullptr) // if no entity, print space
      {
        std::cout << "   |";
      }
      else //if entity, check the type and output acordingly
      {
        Entity::EntityType type = current_entity->getEntityType();

        if (type == Entity::EntityType::DOOR) 
        {
          Door *door = dynamic_cast<Door *>(current_entity);
          if (door->doorGetLocked()) {
            std::cout << "#D" << current_entity->getId() << '|';
          }
          else 
          {
            std::cout << " D" << current_entity->getId() << '|';
          }
          
        }
        else if (type == Entity::EntityType::CHEST) 
        {
          std::cout << "#T "<< '|';
        }
        else if (type == Entity::EntityType::DEATH_LOCATION) 
        {
          std::cout << " X "<< '|';
        }
        else if (type == Entity::EntityType::CHARACHTER) 
        {
          Entity::CharacterType char_type = current_entity->getCharType();

          if (char_type == Entity::CharacterType::BARBARIAN) 
          {
            std::cout << " B |";
          }
          else if (char_type == Entity::CharacterType::ROGUE) 
          {
            std::cout << " R |";
          }
          else if (char_type == Entity::CharacterType::WIZARD) 
          {
            std::cout << " W |";
          }
          else if (char_type == Entity::CharacterType::ZOMBIE) 
          {
            std::cout << " Z" << current_entity->getId() << "|";
          }
          else if (char_type == Entity::CharacterType::GOBLIN) 
          {
            std::cout << " G" << current_entity->getId() << "|";
          }
          else if (char_type == Entity::CharacterType::LICH) 
          {
            std::cout << " L" << current_entity->getId() << "|";
          }
        }
      }
    }
    std::cout << "\n";

    //Print lower border
    std::cout << "   ";
    for (int column = 0; column < columns_; column++) 
    {
      std::cout << "+---";
    }
    std::cout << "+\n";
  }
};

///---------------------------------------------------------------------------------------------------------------------
std::vector<int> Room::findEmptySpot(int start_row, int start_column) 
{
  //all positions clockwise heading from the north
  std::vector<std::vector<int>> directions = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, 2}, {0, 2}, 
    {1, 2}, {2, 2}, {2, 1}, {2, 0}, {2, -1}, {2, -2}, {1, -2}, {0, -2}, {-1, -2}, {-2, -2}, {-2, -1}, {-3, 0}, {-3, 1}, 
    {-3, 2}, {-3, 3}, {-2, 3}, {-1, 3}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {3, 2}, {3, 1}, {3, 0}, {3, -1}, {3, -2}, 
    {3, -3}, {2, -3}, {1, -3}, {0, -3}, {-1, -3}, {-2, -3}, {-3, -3}, {-3, -2}, {-3, -1}
  };
  
  //find empty spot
  for (auto positions : directions) 
  {
    std::vector<int> new_derections (2);
    new_derections[0] = start_row + positions[0];
    new_derections[1] = start_column + positions[1];

    if (new_derections[0] >= 0 && new_derections[1] >= 0 && new_derections[0] < rows_ && new_derections[1] < columns_) 
    {
      if (fields_[new_derections[0]][new_derections[1]]->getEntity() == nullptr) 
      {
        return new_derections;
      }
    }
  }
  return {};
}

///---------------------------------------------------------------------------------------------------------------------
void Room::printEnemies(void) 
{
  std::cout << "   ";
  int count = 0;
  int max = alive_enemies_;

  std::vector<Character *> sorted_enemies = sortEnemies();

  for (Character *enemy : sorted_enemies) {
    if (enemy->isAlive()) {
      char sign = enemy->getFullName()[0];
      count++;
      std::cout << sign << enemy->getId() << ": " << enemy->getHP() << "/" << enemy->getMaxHP();
      if (count < max) 
      {
        std:: cout << ", ";
      }
      else 
      {
        std::cout << "\n";
      }
    }
  }

};

///---------------------------------------------------------------------------------------------------------------------
std::string Room::getEnemiesSigns(void) 
{
  //init all values to false
  std::string signs;
  bool zombie = false;
  bool goblin = false;
  bool lich = false;

  //check every enemie type
  for (Character *enemy : enemies_) 
  {
    if (enemy->isAlive() && enemy->getCharType() == Entity::CharacterType::LICH) 
    {
      lich = true;
    }
    else if (enemy->isAlive() && enemy->getCharType() == Entity::CharacterType::ZOMBIE) 
    {
      zombie = true;
    }
    else if (enemy->isAlive() && enemy->getCharType() == Entity::CharacterType::GOBLIN) 
    {
      goblin = true;
    }
  }
  
  //if present, assign
  if (goblin) 
  {
    signs.push_back('G');
  }
  if (lich) 
  {
    signs.push_back('L');
  }
  if (zombie) 
  {
    signs.push_back('Z');
  }
  return signs;
}

///---------------------------------------------------------------------------------------------------------------------
Room *Room::findRoom(int room_id, std::vector<Room *> rooms) 
{
  for (Room *room : rooms) 
  {
    if (room->getId() == room_id) 
    {
      return room;
    }
  }
  return nullptr;
}

///---------------------------------------------------------------------------------------------------------------------
std::vector<Character *> Room::getEnemies()
{
  return enemies_;
}

///---------------------------------------------------------------------------------------------------------------------
void Room::SwitchEnteredFirst()
{
  entered_first_ = false;
}

///---------------------------------------------------------------------------------------------------------------------
void Room::setAliveEnemies(int count) 
{
  alive_enemies_ = count;
}

///---------------------------------------------------------------------------------------------------------------------
int Room::countPossibleFields(std::vector<int> position) 
{
  std::vector<std::vector<int>> derections = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

  int count = 0;
  int start_row = position[0];
  int start_column = position[1];

  for (auto positions : derections) 
  {
    std::vector<int> new_derections (2);
    new_derections[0] = start_row + positions[0];
    new_derections[1] = start_column + positions[1];

    if (new_derections[0] >= 0 && new_derections[1] >= 0 && new_derections[0] < rows_ && new_derections[1] < columns_) 
    {
      count++;
    }
  }

  return count;
}

///---------------------------------------------------------------------------------------------------------------------
std::vector<int> Room::identifyRandomPosition(int random_number, std::vector<int> position) 
{
  std::vector<std::vector<int>> derections = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

  int count = 0;
  int start_row = position[0];
  int start_column = position[1];

  for (auto positions : derections) 
  {
    std::vector<int> new_derections (2);
    new_derections[0] = start_row + positions[0];
    new_derections[1] = start_column + positions[1];

    if (new_derections[0] >= 0 && new_derections[1] >= 0 && new_derections[0] < rows_ && new_derections[1] < columns_) 
    {
      count++;
      if (count == random_number) 
      {
        return new_derections;
      }
    }
  }

  return {start_row, start_column};
}

///---------------------------------------------------------------------------------------------------------------------
void Room::enemyPhase(std::vector<Player *> players) 
{
  std::vector<Character *> enemies_sorted = sortEnemies();

  for (auto& enemy : enemies_sorted) 
  {
    if (!enemy->attack(this, players, fields_)) 
    {
      enemy->move(this);
    }
  }

}

///---------------------------------------------------------------------------------------------------------------------
void Room::resetCharacters() 
{

  for (int row = 0; row < rows_; row++) 
  {
    for (int column = 0; column < columns_; column++) 
    {
      if (fields_[row][column]->getEntity() != nullptr && 
      fields_[row][column]->getEntity()->getEntityType() == Entity::EntityType::CHARACHTER) 
      {

        fields_[row][column]->delEntity();

      }
    }
  }

}

///---------------------------------------------------------------------------------------------------------------------
std::vector<Character *> Room::sortEnemies() 
{
  std::vector<Character *> goblins;
  std::vector<Character *> lich;
  std::vector<Character *> zombies;

  for (Character *enemy : enemies_) 
  {
    if (enemy == nullptr || !enemy->isAlive()) continue;

    switch (enemy->getCharType())
    {
      case Entity::CharacterType::GOBLIN:
        goblins.push_back(enemy);
        break;
      case Entity::CharacterType::LICH:
        lich.push_back(enemy);
        break;
      case Entity::CharacterType::ZOMBIE:
        zombies.push_back(enemy);
        break;
      default:
        break;
      }
    }

  std::vector<Character *> sortedEnemies;

  if (!goblins.empty()) 
  {
    std::sort(goblins.begin(), goblins.end(), [](Character* a, Character* b) {
      return a->getId() < b->getId();
    });

    for (Character * character : goblins)
    {
      sortedEnemies.push_back(character);
    }
  }

  if (!lich.empty()) 
  {
    std::sort(lich.begin(), lich.end(), [](Character* a, Character* b) {
      return a->getId() < b->getId();
    });

    for (Character * character : lich)
    {
      sortedEnemies.push_back(character);
    }
  }

  if (!zombies.empty())
  {
    std::sort(zombies.begin(), zombies.end(), [](Character* a, Character* b) {
      return a->getId() < b->getId();
    });

    for (Character * character : zombies)
    {
      sortedEnemies.push_back(character);
    }
  }

  return sortedEnemies;
}
