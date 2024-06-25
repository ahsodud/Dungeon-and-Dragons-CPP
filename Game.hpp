///---------------------------------------------------------------------------------------------------------------------
/// Game.hpp
///
/// Authors: Group-015
///---------------------------------------------------------------------------------------------------------------------

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include <map>

#include "Entity.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Room.hpp"
#include "Field.hpp"
#include "Command.hpp"
#include "Random.hpp"
#include "Utils.hpp"
#include "Random.hpp"
#include "CommandLine.hpp"

///-------------------------------------------------------------------------------------------------------------------
/// Game class
/// Is the main class in application control. 
///
class Game
{
  public:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Enum class for game phase
    /// 
    enum class Phase : char 
    {
      PLAYER,
      ENEMY,
      END
    };

  private:
    ///-------------------------------------------------------------------------------------------------------------------
    /// Map* map_ - all rooms of dungeon together
    /// bool printingMap - is map output enabled
    /// bool printingStory - is story output enabled
    /// bool action_ - actions toggle
    /// int actions_ - total number of actions
    /// int actions_in_current_phase - total number of actions in current phase
    /// Room* current_room_ - a pointer to a current room
    /// int completed_rooms_ - number of completed rooms
    /// int rooms_ - total number of rooms
    /// vector<PLayer*> - vector of players
    /// int active_players_ - number of alive player
    /// Phase phase_ - current phase
    /// std::map<std::string, std::string> messages_ - map of messages
    /// string enemies_met_ - used for print enemies texts
    ///
    Map* map_;
    bool printingMap;
    bool printingStory;
    bool action_;
    int actions_;
    int actions_in_current_phase_;
    Room* current_room_;
    int completed_rooms_;
    int rooms_;
    std::vector<Player*> players_ ;
    int active_players_;
    Phase phase_;
    std::map<std::string, std::string> messages_;
    std::string enemies_met_;

  public:

    // Constructor
    Game();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Constructs a Game object with the given dungeon and story files.
    ///
    /// @param dungeon_file The file containing dungeon info
    /// @param story_file The file containing story lines
    Game(char* dungeon_file, char* story_file);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Copy constructor deleted exp
    ///
    Game(const Game &Game2)  = delete;

    ///---------------------------------------------------------------------------------------------------------------------
    /// Destructor for the Game class, deletes players
    ///
    ~Game();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Deploys players into the current room near the specified door.
    ///
    /// @param door_id The id of the door near which players will be deployed.
    void deployPlayers(int door_id);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Parses the story file and populates the messages map accordingly.
    ///
    /// @param story_file The file containing the story lines
    void parseStoryFile(char* story_file);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Checks if the provided configuration file is a valid story configuration.
    ///
    /// @param config_path The path to the configuration file.
    ///
    /// @return True if the configuration file is valid for a story, false otherwise.
    static bool isValidConfigStory(char* config_path);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Checks if the provided configuration file is a valid dungeon configuration.
    ///
    /// @param config_path The path to the configuration file.
    ///
    /// @return True if the configuration file is valid for a dungeon, false otherwise.
    static bool isValidConfigDungeon(char* config_path);
    
    ///---------------------------------------------------------------------------------------------------------------------
    /// Checks if the game is currently running.
    ///
    /// @return True if the game is running, false otherwise.
    bool isRunning(void);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Starts the game by prompting players to join and setting up initial game state.
    ///
    /// @return 0 on successful start, 1 if the user chooses to quit.
    int start(void);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Executes the given command.
    ///
    /// @param command The command to be executed.
    ///
    void execute(Command command);


    ///---------------------------------------------------------------------------------------------------------------------
    /// Prints a message identified by the given key.
    ///
    /// @param key The key to identify the message to be printed.
    void printMessage(std::string key);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Prints the current room including its message, map, and enemies.
    ///
    void printRoom();


    ///---------------------------------------------------------------------------------------------------------------------
    /// Rolls a set of dice and returns the total value.
    ///
    /// @param dice_amount The number of dice to roll.
    /// @param dice_upper_bound The upper bound (exclusive) for each dice roll.
    ///
    /// @return The total value obtained by rolling the dice.
    static int rollDice(int dice_amount, int dice_upper_bound);

  private:
    ///---------------------------------------------------------------------------------------------------------------------
    /// Adds a player to the game.
    ///
    /// @param player Pointer to the player object to be added.
    ///
    void addPlayer(Player* player);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Prints messages corresponding to enemy signs.
    ///
    /// This function takes a string of signs representing enemies and prints messages for each enemy sign.
    /// The messages are retrieved from the resource files using keys constructed from the prefix "N_ENEMY_" 
    /// followed by each character in the input string.
    ///
    /// @param signs A string containing signs representing enemies.
    ///
    void printEnemiesMessages(std::string signs);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Enters a new room within the dungeon, resetting character positions and values as needed.
    ///
    /// @param room Pointer to the room to enter.
    void enterRoom(Room *room);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Exits the dungeon, triggering the end of the game and printing a farewell message.
    ///
    void exitDangeon();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Uses a health potion from the player's inventory.
    ///
    /// @param player The player using the health potion.
    /// @param abbr The abbreviation of the health potion to be used.
    void useHealthPotion(Player* player, std::string abbr);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Uses a resistance potion from the player's inventory.
    ///
    /// @param player The player using the resistance potion.
    /// @param abbr The abbreviation of the resistance potion to be used.
    void useResistancePotion(Player* player, std::string abbr);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Uses an armor item from the player's inventory, potentially equipping it.
    ///
    /// @param player The player using the armor item.
    /// @param abbr The abbreviation of the armor item to be used.
    void useArmor(Player* player, std::string abbr);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Uses a weapon item from the player's inventory, potentially equipping it.
    ///
    /// @param player The player using the weapon item.
    /// @param abbr The abbreviation of the weapon item to be used.
    void useWeapon(Player* player, std::string abbr);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Searches for an item by its abbreviation in a vector of items.
    ///
    /// @param vector The vector of items to search.
    /// @param abbr The abbreviation of the item to find.
    ///
    /// @return True if the item is found, false otherwise.
    bool findItemByAbbr(std::vector<Item> vector, std::string abbr);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Determines the next move in the game based on the current phase and player/enemy status.
    ///
    void nextMove();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Checks if all enemies in the current room are dead.
    ///
    /// @return True if all enemies are dead, false otherwise.
    //
    bool allEnemiesDead();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Checks if all players in the game are dead.
    ///
    /// @return True if all players are dead, false otherwise.
    //
    bool allPlayersDead();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Saves endgame data to a file specified by the given path. Writes player survival status, completed rooms count,
    /// and performed actions count.
    ///
    /// @param path The file path where the data will be saved.
    ///
    void saveData(std::string path);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Prints endgame statistics including player survival status, completed rooms count, and performed actions count.
    ///
    void printEndGameStatistic();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Ends the game, printing endgame statistics and prompting the user to save the data.
    ///
    void end();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Enemy phase logic. Tryies to attack
    ///
    void enemyPhase();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Executes the "help" command, displaying information about available commands and their usage.
    ///
    void helpCommand();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Toggles the printing of story messages on or off.
    ///
    void storyCommand();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Toggles the printing of the map on or off.
    ///
    void mapCommand();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Displays the current positions of players and enemies within the room.
    ///
    void posCommand();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Executes the player command, displaying information about a specific player.
    ///
    /// @param param A vector containing parameters for command
    ///
    void playerCommand(std::vector<std::string> param);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Executes the "inventory" command, displaying the inventory of a specific player.
    ///
    /// @param param A vector containing parameters for command
    ///
    void inventoryCommand(std::vector<std::string> param);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Moves a player character to the specified position within the current room.
    ///
    /// @param param A vector containing the character type and target coordinates.
    void moveCommand(std::vector<std::string> param);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Executes the "attack" command, allowing the player to attack with the equipped weapon on the given position.
    ///
    /// @param param A vector of strings containing the parameters for the command.
    ///
    void attackCommand(std::vector<std::string> param);
    
    ///---------------------------------------------------------------------------------------------------------------------
    /// Executes the "loot" command, allowing a player to loot items from a chest or a death location.
    ///
    /// @param param A vector containing the command parameters: [0] character type, [1] coordinates of the target location.
    ///
    void lootCommand(std::vector<std::string> param);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Uses an item or potion specified by the command parameters.
    ///
    /// @param param A vector containing the character type and item to use.
    void useCommand(std::vector<std::string> param);

    void giveCommand(std::vector<std::string> param);

    ///---------------------------------------------------------------------------------------------------------------------
    /// Executes the player phase, displaying the room and prompting the player for their next action.
    ///
    void playerPhase();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Resets game values to when a room is entered
    ///
    void resetValues();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Opens doors in the current room if they are locked.
    ///
    /// This function iterates through all fields in the current room. If a field contains a locked door,
    /// it opens the door. After opening the doors, it increments the number of completed rooms if any doors
    /// were opened.
    ///
    void openDoors();

    ///---------------------------------------------------------------------------------------------------------------------
    /// Prints items inside the given vector. Used in use and loot command
    ///
    /// @param header header for output, for example " Armor :" and etc
    /// @param items items to be printed
    ///
    void printItems(const std::string& header, std::vector<Item*>& items);
};

#endif // GAME_HPP