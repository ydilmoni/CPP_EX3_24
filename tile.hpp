#ifndef TILE_HPP
#define TILE_HPP

#define RESET "\033[0m"
#define RED "\033[31m"         /* Red */
#define BLACK "\033[30m"       /* Black */
#define YELLOW "\033[33m"      /* Yellow */
#define WHITE "\033[37m"       /* White */
#define BROWN "\033[38;5;130m" /* Brown */
#define CAMEL "\033[38;5;180m" /* Camel */

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
        string collor;

        Tile(string type, int num, int location);
        Tile() : landType("desert"), number(0), tile_location(0) , collor(CAMEL){}
        Tile(int loc) : landType("desert"), number(0), tile_location(loc), collor(CAMEL) {}

        void setNum(int newNum);
        void setType (string newType);
        int getNum() const;
        string getType() const;
        void printTile() const;
        void hexagon()const;
        // Static member declaration
        static std::map<int, std::vector<int>> tileLocation_to_adjacentNode;
        static std::map<int, std::vector<int>> node_to_adjacentTile;
        
    };
}

#endif // TILE_HPP
