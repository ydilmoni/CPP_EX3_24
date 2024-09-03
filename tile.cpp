
#include "tile.hpp"
#include <map>
#include <iostream>
using namespace std;

namespace ariel
{

    Tile::Tile(string type, int num, int location)
    {
        this->landType = type;
        this->number = num;
        this->tile_location = location;
        if (landType == "W")
        {
            this->collor = BROWN;
        }
        else if (landType == "G")
        {
            this->collor = YELLOW;
        }
        else if (landType == "O")
        {
            this->collor = BLACK;
        }
        else if (landType == "S")
        {
            this->collor = WHITE;
        }
        else if (landType == "B")
        {
            this->collor = RED;
        }
        else
        {
            this->collor = CAMEL;
        }
    }

    void Tile::setNum(int newNum)
    {
        this->number = newNum;
    }

    void Tile::setType(string newType)
    {
        this->landType = newType;
        if (landType == "W")
        {
            this->collor = BROWN;
        }
        else if (landType == "G")
        {
            this->collor = YELLOW;
        }
        else if (landType == "O")
        {
            this->collor = BLACK;
        }
        else if (landType == "S")
        {
            this->collor = WHITE;
        }
        else if (landType == "B")
        {
            this->collor = RED;
        }
        else
        {
            this->collor = CAMEL;
        }
    }
    int Tile::getNum() const
    {
        return this->number;
    }
    string Tile::getType() const
    {
        return this->landType;
    }

}
