This project simulates a simplified version of the popular board game Settlers of Catan using C++ programming language. The simulation includes the game board, players, tiles, cards, and basic game mechanics.


Overview

The project aims to recreate the fundamental aspects of Settlers of Catan in a console-based environment. It incorporates various classes such as Board, Player, Tile, Deck, and others to manage game elements and simulate gameplay.


Features

Board Management:

Generation of randomized game boards with different types of tiles (e.g., forests, hills).
Placement of numbers on tiles to represent resource production rates.
Player Interactions:

Players can build roads, settlements, and cities on the board.
Resource management for players (brick, wood, sheep, grain, ore) and development cards.


Game Mechanics:

Turn-based gameplay where players take actions like building, trading, and buying development cards.
Implementation of basic Catan rules such as resource collection, trading, and victory point calculation.
Installation
Requirements
C++ compiler (supporting C++14 or later)
Standard C++ libraries
Terminal or console environment

git clone https://github.com/ydilmoni/CPP_EX3_24.git

cd CPP_EX3_24

For a quick start, remember to mark line 45: "this->startGame();" in the catan.cpp file as a comment
and uncomment from line 46: "this->spacialStart();" in the same file

g++ main.cpp board.cpp tile.cpp deck.cpp player.cpp -o catan_simulation

./catan_simulation


Usage
Upon running the program, follow the prompts to set up the game and interact with the simulation.
Players can take turns performing actions such as building roads, settlements, and cities, as well as managing resources and development cards.
The game will display board updates, player status, and handle basic game logic to simulate gameplay.


File Structure
The project directory structure includes the following files:

board.hpp, board.cpp: Classes and methods for managing the game board and tile placement.
player.hpp, player.cpp: Classes and methods for managing players, their resources, and actions.
tile.hpp, tile.cpp: Classes and methods for defining and interacting with individual tiles on the game board.
deck.hpp, deck.cpp: Classes and methods for managing the deck of development cards in the game.

File Structure
The project directory structure includes the following files:

board.hpp, board.cpp
Class: Board

Methods:

Board(): Constructor for initializing the board.
initializeTiles(): Initializes the tiles on the board.
setNumAndType(int location, int newNum, string newType): Sets the number and type of a specific tile.
findZero(vector<int> numbers): Helper function to find a zero in a vector.
player.hpp, player.cpp
Class: Player

Methods:

Player(string playerName): Constructor to initialize a player with a given name.
Player(): Default constructor.
addPrivateScore(): Increases the player's private score.
setCollor(string newCollor): Sets the player's color.
getCollor() const: Returns the player's color.
setName(string newName): Sets the player's name.
getName() const: Returns the player's name.
addResurces(string resourceToAdd): Adds a resource to the player's inventory.
addResurces(string resourceToAdd, int amount): Adds a specified amount of a resource to the player's inventory.
removeResurces(string resourceToRemove): Removes a resource from the player's inventory.
removeResurces(string resourceToRemove, int amount): Removes a specified amount of a resource from the player's inventory.
build(): Initiates the building process for the player.
build(string whatToBuild): Builds a specific structure (road, village, city, development card) for the player.
iHave(string cardName): Checks if the player possesses a specific card.
iHave(string cardName, int amount): Checks if the player possesses a specific number of a card.
iCanBuild(string building): Checks if the player can build a specific structure.
resourcesAndKnightIHave(): Returns a vector of resources and knights the player possesses.
iCanBuild(): Returns a vector of structures the player can build.
addRoad(): Increases the count of roads built by the player.
addVillage(): Increases the count of villages built by the player.
addCity(): Increases the count of cities built by the player.
printMyCard(): Prints the player's resource and development card inventory.
cheackScore(): Calculates and returns the player's total score.
printMyTradeOption(): Prints the trading options available to the player.
getMyDVLPCard(): Returns a vector of development cards the player possesses.
getAmountOfResource(string resource): Returns the amount of a specific resource the player possesses.
printMyResources(): Prints the player's resource inventory.
getResourcesDeckSize(): Returns the total number of resources the player possesses.
deck.hpp, deck.cpp
Class: Deck

Methods:

Deck(): Constructor for initializing the deck of development cards.
Deck(string source): Constructor for initializing the deck from a specified source.
ShuffleCards(): Shuffles the deck of development cards.
drawCard(): Draws a card from the deck.
isEmpty() const: Checks if the deck is empty.
printDeck(): Prints all cards in the deck.
addToDeck(string card): Adds a card to the deck.
addToDeck(string card, int amount): Adds a specified number of cards to the deck.
tile.hpp, tile.cpp
Class: Tile

Methods:

Tile(string type, int num, int location): Constructor for initializing a tile with type, number, and location.
Tile(): Default constructor for initializing a tile as a desert tile.
Tile(int loc): Constructor for initializing a tile with a specified location.
setNum(int newNum): Sets the number on the tile.
setType(string newType): Sets the type of the tile.
getNum() const: Returns the number on the tile.
getType() const: Returns the type of the tile.
