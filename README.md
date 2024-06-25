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

## Full Game Example

<details>
<summary>Example</summary>

```

** Welcome to the exciting world of Dungeons & Classes!

How many players want to join the adventure? (1 to 3)
> 2

Player 1 what do you wish to be called? (max length 10 characters)
> David
David, please choose a player type:
  [W] Wizard     0/1
  [B] Barbarian  0/1
  [R] Rogue      0/1
> B

Player 2 what do you wish to be called? (max length 10 characters)
> Alex
Alex, please choose a player type:
  [W] Wizard     0/1
  [B] Barbarian  1/1
  [R] Rogue      0/1
> W

-- Players --------------------------------------
  Player 1: Barbarian [B] "David"
  Player 2: Wizard [W] "Alex"

** You have entered the dungeon of the evil Lich!
** Help the anxious souls of the nearby village by freeing
** them from the monsters that haunt it!

** Beware, there are zombies in this room!

-- ROOM 1 (0/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T |   |#D2|
   +---+---+---+
 2 |   | Z1| B |
   +---+---+---+
 3 |   | W |#D0|
   +---+---+---+
   Z1: 15/15

** What do you want to do?
> positions
Barbarian [B] "David" on (2,3)
Wizard [W] "Alex" on (3,2)
Zombie 1 [Z1] on (2,2)

** What do you want to do?
> player W
Wizard [W] "Alex" on (3,2)
  Armor Value:        0
  Current Health:    10
  Max Health:        10
  Strength:           1
  Vitality:           4

** What do you want to do?
> inventory B
Inventory "David"
  Equipped Armor: [-] None
  Equipped Weapon: [GAXE] Greataxe
  Weapons: [HAXE] Handaxe (2)

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (3,2).
[Dice Roll] 1 d12 resulting in a total value of 3.

Zombie 1 loses 6 health (7 * 100 % - 1).
Alex loses 7 health (7 * 100 % - 0).

-- ROOM 1 (0/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T |   |#D2|
   +---+---+---+
 2 |   | Z1| B |
   +---+---+---+
 3 |   | W |#D0|
   +---+---+---+
   Z1: 9/15

** What do you want to do?
> attack W 2,2
Wizard [W] "Alex" used "Quarterstaff of Force" on (2,2) affecting (2,2).
[Dice Roll] 1 d10 resulting in a total value of 5.

Zombie 1 loses 4 health (5 * 100 % - 1).

-- ROOM 1 (0/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T |   |#D2|
   +---+---+---+
 2 |   | Z1| B |
   +---+---+---+
 3 |   | W |#D0|
   +---+---+---+
   Z1: 5/15

Zombie 1 [Z1] used "Dagger" on (3,2) affecting (3,2).
[Dice Roll] 1 d4 resulting in a total value of 4.

Alex loses 3 health (4 * 100 % - 0).
Alex was defeated.

-- ROOM 1 (0/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T |   |#D2|
   +---+---+---+
 2 |   | Z1| B |
   +---+---+---+
 3 |   | X |#D0|
   +---+---+---+
   Z1: 5/15

** What do you want to do?
> attack W 2,2
!! Unavailable entity or item.
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (3,2).
[Dice Roll] 1 d12 resulting in a total value of 6.

Zombie 1 loses 5 health (10 * 100 % - 1).
Zombie 1 was defeated.

-- ROOM 1 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T |   | D2|
   +---+---+---+
 2 |   | X | B |
   +---+---+---+
 3 |   | X | D0|
   +---+---+---+


** What do you want to do?
> loot B 2,2
** Looting successful! You have received the following items ...
  Weapons: [DAGG] Dagger (1)

-- ROOM 1 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T |   | D2|
   +---+---+---+
 2 |   |   | B |
   +---+---+---+
 3 |   | X | D0|
   +---+---+---+


** What do you want to do?
> loot B 3,2
** Looting successful! You have received the following items ...
  Weapons: [DAGG] Dagger (1), [QACD] Quarterstaff of Acid (1), [QFRC] Quarterstaff of Force (1)

-- ROOM 1 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T |   | D2|
   +---+---+---+
 2 |   |   | B |
   +---+---+---+
 3 |   |   | D0|
   +---+---+---+


** What do you want to do?
> move B 1,2
Barbarian [B] "David" moved to (1,2).

-- ROOM 1 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |#T | B | D2|
   +---+---+---+
 2 |   |   |   |
   +---+---+---+
 3 |   |   | D0|
   +---+---+---+


** What do you want to do?
> loot B 1,1
** To unlock this chest you need to roll at least 4 to reach the 5 needed.
[Dice Roll] 1 d20 resulting in a total value of 13.

** Looting successful! You have received the following items ...
  Armor: [PARM] Plate Armor (1)
  Weapons: [QCLD] Quarterstaff of Cold (1)
  Consumables: [GHEP] Greater Health Potion (3)

-- ROOM 1 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |   | B | D2|
   +---+---+---+
 2 |   |   |   |
   +---+---+---+
 3 |   |   | D0|
   +---+---+---+


** What do you want to do?
> inventory B
Inventory "David"
  Equipped Armor: [-] None
  Equipped Weapon: [GAXE] Greataxe
  Armor: [PARM] Plate Armor (1)
  Weapons: [DAGG] Dagger (2), [HAXE] Handaxe (2), [QACD] Quarterstaff of Acid (1), [QCLD] Quarterstaff of Cold (1), [QFRC] Quarterstaff of Force (1)
  Consumables: [GHEP] Greater Health Potion (3)

** What do you want to do?
> use B PARM

-- ROOM 1 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |   | B | D2|
   +---+---+---+
 2 |   |   |   |
   +---+---+---+
 3 |   |   | D0|
   +---+---+---+


** What do you want to do?
> player B
Barbarian [B] "David" on (1,2)
  Armor Value:        8
  Current Health:    13
  Max Health:        13
  Strength:           4
  Vitality:           1

** What do you want to do?
> move 1,3
!! Invalid AMOUNT OF PARAMETERS.
> move B 1,3
Barbarian [B] "David" moved to (1,3).
** Well done, you made it through the first room!
** Let's see if you can master this one as well!

** We have reached the end of the dungeon!
** Kill the Lich and you should all be celebrated as heroes of the dungeon.


-- ROOM 2 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |   |#D1| B |
   +---+---+---+
 2 |   | L1|   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+
   L1: 50/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 10.

Lich 1 loses 8 health (14 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |   |#D1| B |
   +---+---+---+
 2 |   | L1|   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+
   L1: 42/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 10.

Lich 1 loses 8 health (14 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |   |#D1| B |
   +---+---+---+
 2 |   | L1|   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+
   L1: 34/50

Lich 1 [L1] used "Quarterstaff of Force" on (1,3) affecting (1,3).
[Dice Roll] 1 d10 resulting in a total value of 9.

David loses 1 health (9 * 100 % - 8).

-- ROOM 2 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |   |#D1| B |
   +---+---+---+
 2 |   | L1|   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+
   L1: 34/50

** What do you want to do?
> map

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 4.

Lich 1 loses 2 health (8 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

   L1: 32/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 2.

Lich 1 loses 0 health (6 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

   L1: 32/50

Lich 1 [L1] used "Quarterstaff of Cold" on (1,3) affecting (1,3).
[Dice Roll] 2 d10 resulting in a total value of 11.

David loses 3 health (11 * 100 % - 8).

-- ROOM 2 (1/2 completed) --------------------

   L1: 32/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 10.

Lich 1 loses 8 health (14 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

   L1: 24/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 12.

Lich 1 loses 10 health (16 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

   L1: 14/50

Lich 1 [L1] used "Quarterstaff of Fire" on (1,3) affecting (1,2), (1,3), (2,3).
[Dice Roll] 3 d6 resulting in a total value of 10.

David loses 2 health (10 * 100 % - 8).

-- ROOM 2 (1/2 completed) --------------------

   L1: 14/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 1.

Lich 1 loses 0 health (5 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

   L1: 14/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 7.

Lich 1 loses 5 health (11 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

   L1: 9/50

Lich 1 [L1] used "Quarterstaff of Cold" on (1,3) affecting (1,3).
[Dice Roll] 2 d10 resulting in a total value of 11.

David loses 3 health (11 * 100 % - 8).

-- ROOM 2 (1/2 completed) --------------------

   L1: 9/50

** What do you want to do?
> map
     1   2   3  
   +---+---+---+
 1 |   |#D1| B |
   +---+---+---+
 2 |   | L1|   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 9.

Lich 1 loses 7 health (13 * 100 % - 6).

-- ROOM 2 (1/2 completed) --------------------

     1   2   3  
   +---+---+---+
 1 |   |#D1| B |
   +---+---+---+
 2 |   | L1|   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+
   L1: 2/50

** What do you want to do?
> attack B 2,2
Barbarian [B] "David" used "Greataxe" on (2,2) affecting (1,2), (2,2), (2,3).
[Dice Roll] 1 d12 resulting in a total value of 10.

Lich 1 loses 2 health (14 * 100 % - 6).
Lich 1 was defeated.

** Wow, you are all heroes!! You defeated the Lich!
** Go to the village! The people there have organised
** a huge festival to celebrate you!

-- Players --------------------------------------
  Barbarian [B] "David" survived.
  Wizard [W] "Alex", rest in peace.

-- Statistics -----------------------------------
  2 rooms completed
  19 performed actions

** Enter the file path of a writable file or
** a path for a new file (including the file format e.g. `.txt`).
> saves/game_10.txt
```
</details>
