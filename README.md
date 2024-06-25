# Dungeon and Dragons C++
This is implementation of DnD game using C++. Topics met here are:
- Classes and Objects
- Inheritance, polymorphism
- Smart pointers
- Strings and Streams
- operator overloading and own exeption class
### The Game
The following is just a quick overview of the basic elements of the game, a more detailed description can be found in
Milestone 1 - Basic Structure and Output and Milestone 2 - Game Logic.
In this game, 1 to 3 players explore a dungeon that consists of interconnected rooms. Along the way they have to fight
enemies and can find helpful items.


### Start of the Game
At the beginning of the game each player chooses one of the following three player types. Depending on the chosen type
each player has different stats and base equipment.

**Barbarian**
**Rogue**
**Wizard**


### Playing the Game
The game consists of multiple rounds of two alternating phases, the Player Phase and the Enemy Phase.
In the Player Phase the players can perform actions. When the total number of player actions in this phase
has reached the number of players, the Player Phase ends. If the room the players are currently in contains enemies,
this is followed by the Enemy Phase in which every enemy in the current room either attacks or moves.
Then the next round starts with the next Player Phase. This keeps repeating until the Dungeon Boss (Lich) is killed, the players leave the Dungeon via the
entrance/exit, or all players are defeated.

## Goal of the Game
The main goal of the game is to defeat the dungeon boss and to complete as
many rooms as possible along your journey. A room counts as completed as soon as there are no enemies left in it.
