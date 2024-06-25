///---------------------------------------------------------------------------------------------------------------------
/// Entity.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <string>
#include "Item.hpp"
#include "Room.hpp"

class Item;
class Weapon;

///-------------------------------------------------------------------------------------------------------------------
/// Entity class
/// Is a parent class for charachter, chest, death location and Door
///
class Entity
{
  public:
    ///---------------------------------------------------------------------------------------------------------------
    /// enum for EntityType
    ///
    enum class EntityType : char 
    {
        CHARACHTER,
        CHEST = 'T',
        DOOR = 'D',
        DEATH_LOCATION = 'X'
    };

    ///---------------------------------------------------------------------------------------------------------------
    /// enum for CharacterType
    ///
    enum class CharacterType : char 
    {
        BARBARIAN = 'B',
        ROGUE = 'R',
        WIZARD = 'W',
        ZOMBIE = 'Z',
        GOBLIN = 'G',
        LICH = 'L'
    };

  protected:
    ///---------------------------------------------------------------------------------------------------------------
    /// EntityType type_ - type of entity
    /// CharacterType char_type_ - type of character
    /// int id_ - ID of entity
    /// vector <int> - vector of coordinates
    ///
    EntityType type_;
    CharacterType char_type_;
    int id_;
    std::vector<int> coordinates_; 

  public:
    ///---------------------------------------------------------------------------------------------------------------
    /// Constructor. Set to default
    ///
    Entity() = default;

    ///---------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    ///
    Entity(const Entity &Entity2) = delete;

    ///---------------------------------------------------------------------------------------------------------------
    /// Destructor. Set to default
    ///
    virtual ~Entity() = default;

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for EntityType
    ///
    Entity::EntityType getEntityType(void);

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for ID
    ///
    int getId(void) const;

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for CharacterType
    ///
    CharacterType getCharType() const;

    ///---------------------------------------------------------------------------------------------------------------
    /// Setter for coordinates
    ///
    void setCoordinates(int x, int y);

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for coordinates
    ///
    std::vector<int> getCoordinates() const;
};

///-------------------------------------------------------------------------------------------------------------------
/// Character class
/// Used to represent players and enemies on the field
///
class Character: public Entity 
{
  private:
    ///---------------------------------------------------------------------------------------------------------------
    /// int max_hp_ - max hp
    /// int hp_ - current hp
    /// int base_hp_ - base hp for character
    /// int armor_value_ - armor value
    /// int base_armor_value_ - base armor for character
    /// int strength_ - strength value
    /// int vitality_ - vitality value
    /// DamageType resistance_ - type of resistance
    /// vector<Item*> inventory_ - player's inventory
    /// vector<Item*> weapons_ - player's weapons
    /// vector<Item*> armor_ - player's armor
    /// Item* equipped_weapon_ - equipped weapon
    /// Item* equipped_armor_ - equipped armor
    /// Player* player_ - player for this character
    ///
    int max_hp_;
    int hp_;
    int base_hp_;
    int armor_value_;
    int base_armor_value_;
    int strength_;
    int vitality_;
    Item::DamageType resistance_;
    std::vector<Item*> inventory_;
    std::vector<Item*> weapons_;
    std::vector<Item*> armor_;
    Item* equipped_weapon_;
    Item* equipped_armor_;
    Player* player_;

  public:
    ///---------------------------------------------------------------------------------------------------------------
    /// Constructor for character. Used to assighn character to player
    ///
    Character(char letter, Player* player);

    ///---------------------------------------------------------------------------------------------------------------
    /// Constructor for character. Used to initialize enemies
    ///
    Character(char letter, int enemy_id);

    ///---------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    ///
    Character(const Character &Character2) = delete;

    ///---------------------------------------------------------------------------------------------------------------
    /// Destructor for character
    ///
    virtual ~Character() override;
    
    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for max hp
    ///
    /// @return max hp
    ///
    int getMaxHP() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for hp
    ///
    /// @return hp
    ///
    int getHP() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for armor value
    ///
    /// @return armor value
    ///
    int getArmorValue() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for strength
    ///
    /// @return strength
    ///
    int getStrength() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for vitality
    ///
    /// @return vitality
    ///
    int getVitality() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for resistance
    ///
    /// @return resistanse
    ///
    Item::DamageType getResistance() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for inventory
    ///
    /// @return inventory
    ///
    const std::vector<Item*> getInventory();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for weapons
    ///
    /// @return weapons
    ///
    const std::vector<Item*> getWeapons();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for armor
    ///
    /// @return armor
    ///
    const std::vector<Item*> getArmor();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for full name
    ///
    /// @return full name
    ///
    std::string getFullName() const;
    
    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for equipped weapon
    ///
    /// @return equipped weapon
    ///
    Item* getEquippedWeapon() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for equipped armor
    ///
    /// @return equipped armor
    ///
    Item* getEquippedArmor() const;

    ///-----------------------------------------------------------------------------------------------------------------
    /// Getter for player
    ///
    /// @return player
    ///
    Player* getPlayer() const;
    
    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for character type
    ///
    /// @param char_type charachter type
    ///
    void setCharType(CharacterType char_type);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for max hp
    ///
    /// @param max_hp maximal hp
    ///
    void setMaxHP(int max_hp);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for hp
    ///
    /// @param hp hp
    ///
    void setHP(int hp);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for armor value
    ///
    /// @param armor_value armor value
    ///
    void setArmorValue(int armor_value);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for strength
    ///
    /// @param strength strength
    ///
    void setStrength(int strength);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for vitality
    ///
    /// @param vitality vitality
    ///
    void setVitality(int vitality);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for resistance
    ///
    /// @param resistance resistance
    ///
    void setResistance(Item::DamageType resistance);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for equipped weapon
    ///
    /// @param weapon weapon to equip
    ///
    void setEquippedWeapon(Item* weapon);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Setter for equipped armor
    ///
    /// @param armor armor to equip
    ///
    void setEquippedArmor(Item* armor);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Calculator for max hp
    ///
    void calculateMaxHp();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Calculator for armor
    ///
    /// @param input_value value to adjust
    ///
    void calculateArmor(int input_value);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Adjust armor value
    ///
    /// @param input_value input value
    ///
    void AdjustArmorValue(int input_value);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Add new armor to player's inventory
    ///
    /// @param armor new armor item
    ///
    void addArmor(Item *armor);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Add new weapon to player's inventory
    ///
    /// @param weapon new weapon item
    ///
    void addWeapon(Item *weapon);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Add new item to player's inventory
    ///
    /// @param item new item
    ///
    void addItem(Item *item);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Remove weapon from player's inventory
    ///
    /// @param weapon weapon
    ///
    void eraseWeapon(Item *weapon);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Remove armor from player's inventory
    ///
    /// @param armor armor
    ///
    void eraseArmor(Item *armor);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Remove item from player's inventory
    ///
    /// @param item item
    ///
    void eraseItem(Item *item);
    
    ///-----------------------------------------------------------------------------------------------------------------
    /// Add new armor to player's inventory. Used with loot command
    ///
    /// @param items armor
    ///
    void lootArmor(std::vector<Item *> items);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Add new weapon to player's inventory. Used with loot command
    ///
    /// @param items weapon
    ///
    void lootWeapons(std::vector<Item *> items);
    
    ///-----------------------------------------------------------------------------------------------------------------
    /// Add new consumables to player's inventory. Used with loot command
    ///
    /// @param items consumables
    ///
    void lootConsumables(std::vector<Item *> items);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Used to find desired item
    ///
    /// @param vector where to look for
    /// @param item to check
    ///
    /// @return true, if matched, false othervise
    ///
    static bool findItem(std::vector<Item *> vector, Item* item);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Add new weapon to player's inventory. Used with loot command, works together with previous functions 
    ///
    /// @param vector 
    /// @param item item to add
    ///
    static void addFoundItem(std::vector<Item *> vector, Item* item);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Move command logic for movement inside the room
    ///
    /// @param room map
    ///
    void move(Room *room);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Attack logic.
    ///
    /// @param room room
    /// @param player vector of players
    /// @param fields double vector of fields
    ///
    /// @return true, if successful, false otherwise
    ///
    bool attack(Room *room, std::vector<Player *> players, std::vector<std::vector<Field *>> fields);

    ///-----------------------------------------------------------------------------------------------------------------
    /// This function counts distance between player and targetable entity
    ///
    /// @param player player
    ///
    /// @return distance between player and entity
    ///
    int countDistance(Player *player);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Find target function. Used for enemy turn logic. Finds closest player with least hp
    /// and attacks them
    ///
    /// @param players vector of players
    ///
    int findTarget(std::vector<Player *> players);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Finds adjacent field for provided coordinates
    ///
    /// @param vector<int> coordinates
    ///
    /// @return true, if adjacent, false otherwise
    ///
    bool adjacentField(std::vector<int> coordinates);

    ///-----------------------------------------------------------------------------------------------------------------
    /// This function is used to get random number for melee weapon
    ///
    Weapon *getRandomWeapon();

    ///-----------------------------------------------------------------------------------------------------------------
    /// This function is used to get random number for ranged weapon
    ///
    Weapon *getRandomRangedWeapon();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Function is used to find nearest clockwise position for given coordinates
    ///
    /// @param items weapon
    ///
    int earlierClockwise(std::vector<std::vector<int>> coordinates);

    ///-----------------------------------------------------------------------------------------------------------------
    /// Checks, if character is alive
    ///
    /// @return true, if alive, false otherwise
    ///
    bool isAlive();

    ///-----------------------------------------------------------------------------------------------------------------
    /// Destructor for inventory
    ///
    void clearInventory();

};

///-------------------------------------------------------------------------------------------------------------------
/// Chest class
/// Is a chest with items inside.
///
class Chest: public Entity 
{
  private:
    ///---------------------------------------------------------------------------------------------------------------
    /// vector<Item*> loot_ - items inside the chest
    /// 
    std::vector<Item *> loot_;

  public:
    ///---------------------------------------------------------------------------------------------------------------
    /// Constructor for chest. Takes in items to store and value needed to be rolled to open the chest.
    ///
    /// @param vector<string> vector of items to store
    /// @param value_unlock value, needed to be rolled
    ///
    Chest(std::vector<std::string> items, int value_unlock);

    ///---------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    /// 
    Chest(const Chest &Chest2) = delete;

    ///---------------------------------------------------------------------------------------------------------------
    /// Destructor
    /// 
    virtual ~Chest() override;

    ///---------------------------------------------------------------------------------------------------------------
    /// Getter for loot inside the chest
    /// 
    /// @return loot inside
    ///
    std::vector<Item *>& getLoot();

    ///---------------------------------------------------------------------------------------------------------------
    /// Destructor for inventory of chest
    /// 
    void clearInventory();
};

///-------------------------------------------------------------------------------------------------------------------
/// Death location
/// Stores loot of killed entity
///
class DeathLocation: public Entity
{
  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// vector<Item*> loot_ - loot of dead entity
    ///
    std::vector<Item *> loot_;

  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor for death location. Takes in inventory of entity and coordinates and creates new death loaction
    ///
    /// @param loot loot of dead entity
    /// @param cordinates coordinates of entity
    ///
    DeathLocation(std::vector<Item *> loot, std::vector<int> coordinates);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    ///
    virtual ~DeathLocation() override;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    ///
    DeathLocation(const DeathLocation &DeathLocation2) = delete;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for loot, that stored inside the death location
    ///
    /// @return loot
    ///
    std::vector<Item *>& getLoot();

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor for inventory vector
    ///
    void clearInventory();
};

///-------------------------------------------------------------------------------------------------------------------
/// Door class
/// Has a pointer to next room
///
class Door: public Entity 
{
  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// bool locked_ - locked status 
    /// Room* next_room_ - pointer to next room
    /// int next_room_id_ - ID of next room
    ///
    bool locked_;
    Room* next_room_;
    int next_room_id_;

  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for lock status
    ///
    /// @return true, if locked, false otherwise
    ///
    bool doorGetLocked(void);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for room. Returns room, to which the doors points
    ///
    /// @return true, if locked, false otherwise
    ///
    Room *doorGetRoom(void);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Opens the door
    ///
    void open();

    ///-------------------------------------------------------------------------------------------------------------------
    /// Setter for next room pointer
    ///
    /// @param next_room pointer to next room
    ///
    void setPointer(Room *next_room);

  public: 
    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor for door.
    ///
    Door(int next_room);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    ///
    Door(const Door &Door2) = delete;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    ///
    ~Door() override = default;
};


#endif // ENTITY_HPP