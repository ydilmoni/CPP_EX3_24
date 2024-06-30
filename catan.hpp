
#ifndef CATAN_HPP
#define CATAN_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "deck.hpp"

namespace ariel
{
    class Catan
    {
    private:
        // Private member variables
        std::vector<std::reference_wrapper<Player>> players; // List of players in the game
        Board board;                                         // Game board
        std::map<std::string, Deck> decks;                   // Decks of development cards

        std::map<std::pair<int, int>, Player *> gameEdges;      // Edges on the game board and their owner
        std::vector<std::pair<Player *, std::string>> gameNode; // Nodes on the game board and their building type

        int biggestArmyIndex = -1; // Index of the player with the largest army

        // Private functions
        /**
         * @brief Initializes all nodes to nullptr at the start of the game.
         */
        void initializingGameNode();

        /**
         * @brief Sets the game node with player data.
         * @param nodeIndex The index of the node.
         * @param player The player who owns the node.
         * @param buildingType The type of building on the node.
         */
        void setGameNode(int nodeIndex, Player &player, std::string buildingType);

        /**
         * @brief Prints information about all game nodes.
         */
        void printAllNodeInformation() const;

        /**
         * @brief Returns a vector of all unoccupied nodes where building is possible.
         * @return A vector of unoccupied node indices.
         */
        std::vector<int> getUnoccupiedNodeVector();

        /**
         * @brief Checks if building is possible on a specified node.
         * @param nodeIndex The index of the node.
         * @return True if building is possible, false otherwise.
         */
        bool canBuildThere(int nodeIndex);

        /**
         * @brief Initializes all edges to nullptr at the start of the game.
         */
        void initializingGameEdges();

        /**
         * @brief Sets the game edge with player data.
         * @param start The start point of the edge.
         * @param end The end point of the edge.
         * @param player The player who owns the edge.
         */
        void setGameEdges(int start, int end, Player &player);

        /**
         * @brief Returns a vector of all unoccupied edges connected to a specified village.
         * @param villagePlace The place of the village.
         * @return A vector of unoccupied edges.
         */
        std::vector<std::pair<int, int>> getUnoccupiedConnectedEdges(int villagePlace) const;

        /**
         * @brief Prints information about all game edges.
         */
        void printAllGameEdges() const;

        /**
         * @brief Prints information about all unoccupied edges.
         */
        void printUnoccupiedEdge() const;

        /**
         * @brief Returns a vector of all places where a player can build a road.
         * @param playerIndex The index of the player.
         * @return A vector of possible road locations.
         */
        std::vector<std::pair<int, int>> getPlacesForRoadByPlayerIndex(int playerIndex);

        /**
         * @brief Returns a vector of all places where a player can build a city.
         * @param playerIndex The index of the player.
         * @return A vector of possible city locations.
         */
        std::vector<int> getPlaceForCityByPlayerIndex(int playerIndex);

        /**
         * @brief Returns a vector of all places where a player can build a village.
         * @param playerIndex The index of the player.
         * @return A vector of possible village locations.
         */
        std::vector<int> getPlaceForVillageByPlayerIndex(int playerIndex);

        /**
         * @brief Distributes resources to players based on the rolled number.
         * @param number The rolled number.
         */
        void dealResurces(int number);

    public:
        // Constructors
        /**
         * @brief Constructor for initializing the game with three players.
         * @param p1 Player 1.
         * @param p2 Player 2.
         * @param p3 Player 3.
         */
        Catan(Player &p1, Player &p2, Player &p3);

        /**
         * @brief Default constructor.
         */
        Catan();

        // Game setup methods
        /**
         * @brief Starts the game by setting up initial conditions.
         */
        void startGame();

        /**
         * @brief Manages the first two village placements for all players.
         */
        void first2village();

        /**
         * @brief Helps build the first two villages and roads.
         * @param index The index of the player.
         */
        void putVillageAndRoad(int index);
        /**
         * @brief Builds a free road for a player at the specified location.
         * @param playerIndex The index of the player.
         * @param place The location to build the road.
         */
        void buildFreeRoad(int playerIndex, int place);

        /**
         * @brief Special start for the game where each player has 2 villages and 2 roads.
         */
        void spacialStart();

        // Main gameplay methods
        /**
         * @brief Manages the main gameplay after the initial placement.
         */
        void restOfGame();

        /**
         * @brief Checks if a player can build anything.
         * @param playerIndex The index of the player.
         */
        void iCanBuild(int playerIndex);

        /**
         * @brief Allows a player to build a village during the game.
         * @param playerIndex The index of the player.
         */
        void putVillage(int playerIndex);

        /**
         * @brief Allows a player to build a road during the game.
         * @param playerIndex The index of the player.
         */
        void putRoad(int playerIndex);

        /**
         * @brief Allows a player to build a city during the game.
         * @param playerIndex The index of the player.
         */
        void putCity(int playerIndex);

        /**
         * @brief Manages trading options for a player.
         * @param playerIndex The index of the player.
         */
        void trade(int playerIndex);

        /**
         * @brief Allows a player to trade with another player.
         * @param playerIndex The index of the player.
         */
        void tradeWithPlayer(int playerIndex);

        /**
         * @brief Allows a player to trade with the game (bank).
         * @param playerIndex The index of the player.
         */
        void tradeWithGame(int playerIndex);

        /**
         * @brief Allows a player to buy a development card.
         * @param playerIndex The index of the player.
         */
        void buyDevelopmentCard(int playerIndex);

        /**
         * @brief Allows a player to choose a development card to use.
         * @param playerIndex The index of the player.
         */
        void chooseDevelopmentCard(int playerIndex);

        /**
         * @brief Uses a specified development card for a player.
         * @param card The development card to use.
         * @param playerIndex The index of the player.
         */
        void useDevelopmentCard(std::string card, int playerIndex);

        /**
         * @brief Uses a Knight development card for a player.
         * @param playerIndex The index of the player.
         */
        void useKnight(int playerIndex);

        /**
         * @brief Uses a Road Building development card for a player.
         * @param playerIndex The index of the player.
         */
        void useRoadBuilding(int playerIndex);

        /**
         * @brief Uses a Monopoly development card for a player.
         * @param playerIndex The index of the player.
         */
        void useMonopoly(int playerIndex);

        /**
         * @brief Uses a Year of Plenty development card for a player.
         * @param playerIndex The index of the player.
         */
        void useYearOfPlenty(int playerIndex);

        /**
         * @brief Returns a specified amount of a card to the deck.
         * @param card The card to return.
         * @param amount The amount to return.
         */
        void returnCardToDeck(std::string card, int amount);

        /**
         * @brief Returns a card to the deck.
         * @param card The card to return.
         */
        void returnCardToDeck(std::string card);

        /**
         * @brief Checks the dice roll for special conditions.
         * @param dice The result of the dice roll.
         */
        void checkDice(int dice);

        /**
         * @brief Checks the dice roll for a roll of 7.
         * @param dice The result of the dice roll.
         */
        void check7(int dice);

        // Printing methods
        /**
         * @brief Prints options from a vector of integers.
         * @param vec The vector of integers.
         */
        void printOptionFromVector(std::vector<int> &vec) const;

        /**
         * @brief Prints a vector of strings.
         * @param vec The vector of strings.
         */
        void printVector(std::vector<std::string> &vec) const;

        /**
         * @brief Prints a vector of integers.
         * @param vec The vector of integers.
         */
        void printVector(std::vector<int> &vec);

        /**
         * @brief Prints a vector of pairs of integers.
         * @param vec The vector of pairs of integers.
         */
        void printVector(std::vector<std::pair<int, int>> &vec);

        /**
         * @brief Prints a vector of pairs of Players and strings.
         * @param vec The vector of pairs of Players and strings.
         */
        void printVector(std::vector<std::pair<Player *, std::string>> &vec);

        /**
         * @brief Prints the resources of a specified player.
         * @param playerIndex The index of the player.
         */
        void printMyResource(int playerIndex);

        /**
         * @brief Returns a string representation of a tile's information.
         * @param tileNum The tile number.
         * @return A string representing tile information.
         */
        std::string p(int tileNum);

        /**
         * @brief Returns a string representation of a road's color.
         * @param start The starting point of the road.
         * @param end The ending point of the road.
         * @param whatToPrint The string representation of the road color.
         * @return A string representing the road color.
         */
        std::string pr(int start, int end, std::string whatToPrint);

        /**
         * @brief Returns a string representation of a road's color.
         * @param start The starting point of the road.
         * @param end The ending point of the road.
         * @return A string representing the road color.
         */
        std::string pr(int start, int end);

        /**
         * @brief Returns a string representation of a node's number and type.
         * @param nodeNum The node number.
         * @return A string representing the node number and type.
         */
        std::string p2(int nodeNum);

        /**
         * @brief Returns a string representation of a middle section.
         * @param start The starting point of the middle section.
         * @param end The ending point of the middle section.
         * @return A string representing the middle section.
         */
        std::string m(int start, int end);

        /**
         * @brief Returns a string representation of multiple middle sections.
         * @param amount The number of sections.
         * @param firstStart The starting point of the first section.
         * @param firstEnd The ending point of the first section.
         * @return A string representing multiple middle sections.
         */
        std::string ms(int amount, int firstStart, int firstEnd);

        /**
         * @brief Prints the entire game board.
         */
        void printBoard();
    };

    // Overloaded operators

    /**
     * @brief Overloaded operator to repeat a string multiple times.
     * @param s The string to repeat.
     * @param n The number of times to repeat the string.
     * @return The repeated string.
     */
    std::string operator*(const std::string &s, int n);

    /**
     * @brief Overloaded operator to repeat a string multiple times.
     * @param n The number of times to repeat the string.
     * @param s The string to repeat.
     * @return The repeated string.
     */
    std::string operator*(int n, const std::string &s);

} // namespace ariel

#endif // CATAN_HPP
