

#ifndef BOARD_HPP
#define BOARD_HPP

#include "tile.hpp"  // Include the header file for Tile class
#include "player.hpp"  // Include the header file for Player class
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <iomanip>

namespace ariel
{
    class Board
    {
    private:
        /**
         * @brief Initializes the tiles on the board with random types and numbers.
         * 
         * This function initializes the game board by creating Tile objects for each position,
         * assigning random types ("W", "B", "G", "S", "O", "D" for water, brick, grain, sheep, ore, desert)
         * and random numbers (2 to 12, with '0' for desert) to each tile.
         */
        void initializingTiles();

        /**
         * @brief Sets the number and type of a specific tile on the board.
         * 
         * @param location The index of the tile to set.
         * @param newNum The new number to set for the tile.
         * @param newType The new type (resource) to set for the tile.
         */
        void setNumAndType(int location, int newNum, std::string newType);

        /**
         * @brief Finds the index of the first occurrence of '0' in a vector of numbers.
         * 
         * @param numbers The vector of numbers to search.
         * @return The index of the first occurrence of '0', or -1 if not found.
         */
        int findZero(std::vector<int> numbers);

    public:
        std::vector<Tile> tiles;  // Vector to store all tiles on the board
        static std::map<int, std::vector<int>> tileLocation_to_adjacentNode;  // Static map: tile to adjacent nodes
        static std::map<int, std::vector<int>> node_to_adjacentTile;  // Static map: node to adjacent tiles
        static std::map<int, std::vector<int>> node_to_adjacentNode;  // Static map: node to adjacent nodes

        /**
         * @brief Constructor for the Board class.
         * 
         * Initializes the board by calling initializingTiles() to set up the initial state.
         */
        Board();
    };
}

#endif // BOARD_HPP
