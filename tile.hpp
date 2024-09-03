

#ifndef TILE_HPP
#define TILE_HPP

// ANSI color codes for console output
#define RESET "\033[0m"
#define RED "\033[31m"         /* Red */
#define BLACK "\033[30m"       /* Black */
#define YELLOW "\033[33m"      /* Yellow */
#define WHITE "\033[37m"       /* White */
#define BROWN "\033[38;5;130m" /* Brown */
#define CAMEL "\033[38;5;180m" /* Camel */

#include <vector>
#include <map>
#include <string>
#include <iostream> // For std::cout, std::endl
using namespace std;

namespace ariel
{
    class Tile
    {
    public:
        // Public member variables
        string landType;         // Type of land on the tile
        int number;              // Number on the tile
        int tile_location;       // Location of the tile
        string collor;           // Color of the tile

        // Constructors
        Tile(string type, int num, int location);    // Parameterized constructor
        Tile() : landType("desert"), number(0), tile_location(0), collor(CAMEL) {}   // Default constructor
        Tile(int loc) : landType("desert"), number(0), tile_location(loc), collor(CAMEL) {} // Constructor with location

        // Setter and getter methods
        void setNum(int newNum);        // Sets the number on the tile
        void setType(string newType);   // Sets the type of land on the tile
        int getNum() const;             // Gets the number on the tile
        string getType() const;         // Gets the type of land on the tile

        // Static member declarations
        static std::map<int, std::vector<int>> tileLocation_to_adjacentNode;   // Map of tile locations to adjacent nodes
        static std::map<int, std::vector<int>> node_to_adjacentTile;           // Map of nodes to adjacent tiles
    };
}

#endif // TILE_HPP
