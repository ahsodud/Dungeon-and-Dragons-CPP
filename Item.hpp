///---------------------------------------------------------------------------------------------------------------------
/// Item.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef ITEM_HPP
#define ITEM_HPP

#include <vector>
#include <string>
#include "Room.hpp"
#include "Item.hpp"
#include "Random.hpp"
#include "Command.hpp"

///-------------------------------------------------------------------------------------------------------------------
/// Item class
/// Is a parent class for all items.
///
class Item
{   
  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Enum class for item type
    ///
    enum class ItemType : char 
    {
        ARMOR,
        WEAPON,
        CONSUMABLES
    };

    ///-------------------------------------------------------------------------------------------------------------------
    /// Enum class for damage type
    ///
    enum class DamageType : char 
    {
        PHYSICAL,
        COLD,
        FIRE,
        ACID,
        FORCE,
        NONE
    };

  protected:
    ///-------------------------------------------------------------------------------------------------------------------
    /// string abbreviation_ - short name of the item
    /// string full_name_ - full name of the item
    /// int amount_ - amount of this item
    /// ItemType type_ - type of this item
    ///
    std::string abbreviation_;
    std::string full_name_;
    int amount_;
    Item::ItemType type_;

  public:

    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor, set to default
    ///
    Item() = default;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Another constructor. Takes in name of the item and amount, assighns characteristics accordingly
    ///
    Item(std::string item, int amount);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    ///
    Item(const Item &Item2) = delete;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    ///
    virtual ~Item() = default;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for amount of items
    ///
    /// @return amount of items
    ///
    int getAmount() const;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for name of the item
    ///
    /// @return full name
    ///
    std::string getName() const;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for abbreviatiation of the item
    ///
    /// @return short name
    ///
    std::string getAbbreviation() const;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for Item type
    ///
    /// @return type of the item
    ///
    Item::ItemType getItemType();

    ///-------------------------------------------------------------------------------------------------------------------
    /// Setter for the amount of the item
    ///
    /// @param amount new amount of item
    ///
    void setAmount(int amount);


    ///-------------------------------------------------------------------------------------------------------------------
    /// Checker for alive players
    ///
    /// @return true, if all players are dead, false otherwise
    ///
    static bool allPlayersDead(std::vector<Player *> players);
    
    ///-------------------------------------------------------------------------------------------------------------------
    /// Overloaded operator for more comfortable item comparison
    ///
    bool operator==(const Item& other) const {
        return abbreviation_ == other.abbreviation_ &&
               full_name_ == other.full_name_ &&
               amount_ == other.amount_ &&
               type_ == other.type_;
    }

    ///-------------------------------------------------------------------------------------------------------------------
    /// Overloaded output operator for more easily output
    ///
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};


///-------------------------------------------------------------------------------------------------------------------
/// Weapon class
/// Represent all weapons that the game has
///
class Weapon: public Item 
{
  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Enum for attack type
    /// 
    enum class AttackType : char 
    {
      MELEE,
      RANGED
    };
    ///-------------------------------------------------------------------------------------------------------------------
    /// Enum for damage pattern
    /// 
    enum class DamagePattern : char 
    {
      HIT,
      SLASH,
      THRUST,
      SHOT,
      BURST,
      LINE
    };

  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// AttackType attack_type_ - type of attack, either melee or ranged
    /// Item::DamageType dmg_type_ - damage type
    /// DamagePattern dmg_pattern_ - damage pattern
    /// int dice_amount - dice amount
    /// int damage_per_dice_ - damage per 1 dice
    /// bool str_based_ - if strength based, adds some damage
    /// bool staff_ - is weapon a staff
    /// bool lich_ - does the lich use this weapon or not
    /// 
    AttackType attack_type_;
    Item::DamageType dmg_type_;
    DamagePattern dmg_pattern_;
    int dice_amount_;
    int damage_per_dice_;
    bool str_based_;
    bool staff_;
    bool lich_;

  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor for weapon. Takes in name and amount, creates object and assighns characteristics accordingly
    /// 
    Weapon(std::string item, int amount);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    /// 
    Weapon(const Weapon &Weapon2) = delete;
    
    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    /// 
    virtual ~Weapon() override = default;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Used for check, if target is in reach.
    ///
    /// @param attacker character, who attacks
    /// @param target target field
    /// @param room current room
    /// @param players vector of players
    /// 
    /// @return error, if no error, then the "NO_ERROR" returned
    ///
    Command::Errors attackTarget(Character* attacker, Field* target, Room* room, std::vector<Player *> players);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for attack type
    ///
    /// @return melee, if melee, ranged, if ranged
    ///
    Weapon::AttackType getAttackType();

  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Attack for staff logic.
    ///
    /// @param attacker character, who attacks
    /// @param target target field
    /// @param room current room
    /// @param players vector of players
    /// 
    /// @return true, if possible, false otherwise
    ///
    bool attackForStaff(Character* attacker, Field* target, Room* room, std::vector<Player *> players);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Attack for melee weapon logic.
    ///
    /// @param attacker character, who attacks
    /// @param target target field
    /// @param room current room
    /// @param players vector of players
    /// 
    /// @return true, if possible, false otherwise
    ///
    bool attackForMelee(Character* attacker, Field* target, Room* room, std::vector<Player *> players);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Attack for ranged weapon logic.
    ///
    /// @param attacker character, who attacks
    /// @param target target field
    /// @param room current room
    /// @param players vector of players
    /// 
    /// @return true, if possible, false otherwise
    ///
    bool attackForRanged(Character* attacker, Field* target, Room* room, std::vector<Player *> players);

    ///-------------------------------------------------------------------------------------------------------------------
    /// This function displays affected fields on the map after slash attack.
    ///
    /// @param attacker_cords character, who attacks
    /// @param target_cords target field
    /// @param room current room
    /// @param affected_fields vector of affected fields
    ///
    void slashDmgPattern(std::vector<int>& attacker_cords, 
                          std::vector<int>& target_cords, Room* room,
                          std::vector<Field*>& affected_fields);

    ///-------------------------------------------------------------------------------------------------------------------
    /// This function displays affected fields on the map after thrust attack.
    ///
    /// @param attacker_cords character, who attacks
    /// @param target_cords target field
    /// @param room current room
    /// @param affected_fields vector of affected fields
    ///
    void thrustDmgPattern(std::vector<int>& attacker_cords,
                          std::vector<int>& target_cords, Room* room, 
                          std::vector<Field*>& affected_fields);
    
    ///-------------------------------------------------------------------------------------------------------------------
    /// This function displays affected fields on the map after line attack.
    ///
    /// @param attacker_cords character, who attacks
    /// @param target_cords target field
    /// @param room current room
    /// @param affected_fields vector of affected fields
    ///
    void lineDmgPattern(std::vector<int>& attacker_cords, 
                        std::vector<int>& target_cords, Room* room, 
                        std::vector<Field*>& affected_fields);

    ///-------------------------------------------------------------------------------------------------------------------
    /// This function displays affected fields on the map after burst attack.
    ///
    /// @param target_cords target field
    /// @param room current room
    /// @param affected_fields vector of affected fields
    ///
    void burstDmgPattern(std::vector<int>& target_cords, Room* room,
                          std::vector<Field*>& affected_fields);
    
    ///-------------------------------------------------------------------------------------------------------------------
    /// This function applies damage to characters, that are on the affected fields
    ///
    /// @param affected_fields vector of affected fields
    /// @param attacker character, who attacks
    /// @param target_cords target field
    /// @param dmg_mod damage modificator
    /// @param players vector of players
    ///
    void applyDamage(std::vector<Field*>& affected_fields, Character* attacker, 
                      std::vector<int>& target_cords, int dmg_mod, std::vector<Player *> players);
    void calculateDamage(Character* character, Field* char_field, int dmg_mod);

};

///-------------------------------------------------------------------------------------------------------------------
/// Armor class
/// Represent all armors that are inside the game
///
class Armor: public Item 
{
  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// int armor_value_ - armor value
    /// 
    int armor_value_;

  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor for armor. Takes in name and amount, creates object and assighns characteristics accordingly
    /// 
    Armor(std::string item, int amount);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constuctor. Deleted
    /// 
    Armor(const Armor &Armor2) = delete;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    /// 
    virtual ~Armor() override = default;
    
    ///-------------------------------------------------------------------------------------------------------------------
    /// Puts the armor item on character
    /// 
    /// @param character character to dress
    ///
    void applyArmor(Character* character);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for armor value
    /// 
    /// @return armor value
    ///
    int getArmorValue();
};

///-------------------------------------------------------------------------------------------------------------------
/// Amunition class
/// Represent arrow and etc, that are inside the game
///
class Ammunition: public Item 
{
  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor for ammunition. Takes in name and amount, creates object and assighns characteristics accordingly
    /// 
    Ammunition(std::string item, int amount);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    /// 
    Ammunition(const Ammunition &Ammunition2) = delete;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    /// 
    virtual ~Ammunition() override = default;
};

///-------------------------------------------------------------------------------------------------------------------
/// Health potions class
/// Represent health potions, that are inside the game
///
class HealthPotions: public Item 
{
  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// int dice_amount_ - dice ammount
    ///
    int dice_amount_;

  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor for potions. Takes in name and amount, creates object and assighns characteristics accordingly
    ///
    HealthPotions(std::string item, int amount);

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    ///
    HealthPotions(const HealthPotions &HealthPotions2) = delete;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    ///
    virtual ~HealthPotions() override = default;
    
    ///-------------------------------------------------------------------------------------------------------------------
    /// Function, that restores health to the given character
    ///
    /// @param character character to heal
    ///
    int restoreHealth(Character* character);
};

///-------------------------------------------------------------------------------------------------------------------
/// Resistance potions class
/// Represent resistance potions, that are inside the game
///
class ResistPotions: public Item 
{
  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Item::DamageType resist_type_ - type of resistance, which the potion gives
    ///
    Item::DamageType resist_type_;

  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Constructor for potions. Takes in name and amount, creates object and assighns characteristics accordingly
    ///
    ResistPotions(std::string item, int amount);

    ResistPotions(Item::DamageType resist_type) : resist_type_(resist_type) {}

    ///-------------------------------------------------------------------------------------------------------------------
    /// Copy constructor. Deleted
    ///
    ResistPotions(const ResistPotions &ResistPostions2) = delete;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Destructor
    ///
    virtual ~ResistPotions() override = default;

    ///-------------------------------------------------------------------------------------------------------------------
    /// Getter for resist type
    ///
    /// @return resist type
    ///
    Item::DamageType getResistType() const;

    ///-------------------------------------------------------------------------------------------------------------------
    /// This fucntion applies resistance to desired character
    ///
    /// @param character character, to which assighn resistance
    ///
    void applyResist(Character* character);
};

#endif 