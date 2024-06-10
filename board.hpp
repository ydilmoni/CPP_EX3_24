#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "tile.hpp"

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
        std::vector<Tile> tiles;
        Board();

        static std::map<int, std::vector<int>> tileLocation_to_adjacentNode;
        static std::map<int, std::vector<int>> node_to_adjacentTile;
        static std::map<int,std::vector<int>> node_to_adjacentNode;
    };
}

#endif // BOARD_HPP