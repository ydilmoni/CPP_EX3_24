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
    }
    int Tile::getNum() const
    {
        return this->number;
    }
    string Tile::getType() const
    {
        return this->landType;
    }
    void Tile::printTile() const
    {
        hexagon();
    }

    void Tile::hexagon() const
    {
        int side = 3;
        int space = 2;
        space = space > side - 1 ? space : side;

        // first row
        for (int j = 1; j <= space; j++)
        {
            std::cout << " ";
        }
        for (int i = 1; i <= side; i++)
        {
            if (i == 1 || i == side)
            {
                std::cout << "* ";
            }
            else
            {
                std::cout << "- ";
            }
        }
        cout << endl;
        space--;
        // upper rows
        for (int i = 1; i <= side - 2; i++)
        {
            int numChars = side + i - 1;

            for (int j = 1; j <= space; j++)
            {
                std::cout << " ";
            }
            std::cout << "/";
            for (int k = 1; k <= numChars; k++)
            {
                std::cout << "  ";
            }
            std::cout << "\\ ";
            cout << endl;
            space--;
        }
        space--;
        // middle row
        for (int j = 1; j <= space * 2 + 1; j++)
        {
            std::cout << " ";
        }

        string data = this->getType() + " (" + to_string(this->getNum()) + ")";
        for (int j = 1; j <= side * 2; j++)
        {
            if (j == 1 || j == side * 2)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << data;
            }
        }
        cout << endl;
        space++;
        // bottom rows
        for (int i = 1; i <= side - 2; i++)
        {
            int numChars = side * 2 - i - 2;
            for (int j = 1; j <= space; j++)
            {
                std::cout << " ";
            }
            std::cout << " \\";
            for (int k = 1; k <= numChars; k++)
            {
                std::cout << "  ";
            }
            std::cout << "/ ";
            cout << endl;
            space++;
        }
        // last row
        for (int j = 1; j <= space + 1; j++)
        {
            std::cout << " ";
        }
        for (int i = 1; i <= side; i++)
        {
            if (i == 1 || i == side)
            {
                std::cout << "* ";
            }
            else
            {
                std::cout << "- ";
            }
        }
        cout << endl;
    }
    
}
