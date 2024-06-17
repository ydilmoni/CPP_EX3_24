#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "tile.hpp"
#include "catan.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <iomanip>
#include "player.hpp"

namespace ariel
{
    class Board
    {
    private:
        void initializingTiles();
        void setNumAndType(int location, int newNum, string newType);
        int findZero(vector<int> numbers);


    public:
        void printBoard() const;
        void printBoard2();
        std::vector<Tile> tiles;
        Board();
        string p(int tileNum); // print tile information in the collor

        string pr(int start, int end, string whatToPrint);

        

        static std::map<int, std::vector<int>> tileLocation_to_adjacentNode;
        static std::map<int, std::vector<int>> node_to_adjacentTile;
        static std::map<int,std::vector<int>> node_to_adjacentNode;
    };
}

#endif // BOARD_HPP