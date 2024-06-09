#ifndef TILE_HPP
#define TILE_HPP

#include "cardType.hpp"
#include <vector>
#include <map>
#include <string>
using namespace std;

namespace ariel
{
    class Tile
    {
    public:
        string landType;
        int number;
        int tile_location;

        Tile(string type, int num, int location);
        Tile() : landType("desert"), number(0), tile_location(0) {}
        Tile(int loc) : landType("desert"), number(0), tile_location(loc) {}

        void setNum(int newNum);
        void setType (string newType);
        int getNum() const;
        string getType() const;
        string getTypeAsString() const;

        // Static member declaration
        static std::map<int, std::vector<int>> tileLocation_to_adjacentNode;
        static std::map<int, std::vector<int>> node_to_adjacentTile;
    };
}

#endif // TILE_HPP
