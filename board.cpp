#include "board.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <iomanip>

using namespace std;

namespace ariel
{
    void Board::initializingTiles()
    {
        tiles.resize(19);
        for (int i = 0; i < 19; i++)
        {
            tiles[i] = Tile(i + 1);
        }
        vector<string> landTypes = {
            "forest", "forest", "forest", "forest",
            "hills", "hills", "hills",
            "fields", "fields", "fields", "fields",
            "pasture", "pasture", "pasture", "pasture",
            "mountains", "mountains", "mountains",
            "desert"};

        std::vector<int> numbers = {
            2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12, 0};

        // Randomly shuffle the land types and numbers
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(landTypes.begin(), landTypes.end(), g);
        std::shuffle(numbers.begin(), numbers.end(), g);

        // Assign the land types and numbers to the tiles
        for (int i = 0; i < 19; i++)
        {
            if (landTypes[i] == "desert") // so do a swap
            {
                numbers[findZero(numbers)] = numbers[i];
                numbers[i] = 0;
            }
        }

        for (int i = 0; i < 19; i++)
        {
            setNumAndType(i, numbers[i], landTypes[i]);
        }
    }

    int Board::findZero(vector<int> numbers)
    {
        for (int i = 0; i < sizeof(numbers); i++)
        {
            if (numbers[i] == 0)
            {
                return i;
            }
        }
        return -1;
    }

    void Board::setNumAndType(int location, int newNum, string newType)
    {
        tiles[location].setNum(newNum);
        tiles[location].setType(newType);
    }

    void Board::printBoard() const
    {
        cout << endl;
        cout << endl;
        std::vector<int> rows = {3, 4, 5, 4, 3};
        int index = 0;
        for (int row : rows)
        {
            for (int i = 0; i < 5 - row; i++)
            {
                cout << "      ";
            }

            for (int i = 0; i < row; i++)
            {
                cout << tiles[index].getType() << "(" << tiles[index].getNum() << ")";
                // tiles[index].printTile();
                if (i < row - 1)
                    std::cout << "   ";
                index++;
            }
            cout << endl;
            cout << endl;
            cout << endl;
        }
    }

    void Board::printBoard2() const
    {
        std::vector<int> rows = {3, 4, 5, 4, 3};
        int index = 0;

        for (int row = 0; row < rows.size(); row++)
        {
            int numTiles = rows[row];

            for (int line = 0; line < 11; line++) // Each hexagon now takes 9 lines
            {
                for (int space = 0; space < 5 - numTiles; space++)
                {
                    cout << "           "; // Leading spaces for each row
                }

                for (int i = 0; i < numTiles; i++)
                {
                    switch (line)
                    {
                    case 0:
                        cout << "   *********   ";
                        break;
                    case 1:
                        cout << "  *         *  ";
                        break;
                    case 2:
                        cout << " *           * ";
                        break;
                    case 3:
                        cout << "*             *";
                        break;
                    case 4:
                        cout << "* " << tiles[index].getType() << "(" << tiles[index].getNum() << ")       *";
                        break;
                    case 5:
                        cout << "*             *";
                        break;
                    case 6:
                        cout << " *           * ";
                        break;
                    case 7:
                        cout << "  *         *  ";
                        break;
                    case 8:
                        cout << "   *********   ";
                        break;
                    }

                    if (i < numTiles - 1)
                    {
                        if (line == 0 || line == 8)
                            cout << " ";
                        else
                            cout << "   ";
                    }
                    if (line == 8 && i == numTiles - 1)
                        index++;
                }
                cout << endl;
                if (line == 8)
                    index += numTiles - 1; // Adjust index for the next row
            }
        }
    }

    Board::Board()
    {
        initializingTiles();
    }

    std::map<int, std::vector<int>> Board::tileLocation_to_adjacentNode = {
        {1, {1, 2, 3, 9, 10, 11}},
        {2, {3, 4, 5, 11, 12, 13}},
        {3, {5, 6, 7, 13, 14, 15}},
        {4, {8, 9, 10, 18, 19, 20}},
        {5, {10, 11, 12, 20, 21, 22}},
        {6, {12, 13, 14, 22, 23, 24}},
        {7, {14, 15, 16, 24, 25, 26}},
        {8, {17, 18, 19, 28, 29, 30}},
        {9, {19, 20, 21, 30, 31, 32}},
        {10, {21, 22, 23, 32, 33, 34}},
        {11, {23, 24, 25, 34, 35, 36}},
        {12, {25, 26, 27, 36, 37, 38}},
        {13, {29, 30, 31, 39, 40, 41}},
        {14, {31, 32, 33, 41, 42, 43}},
        {15, {33, 34, 35, 43, 44, 45}},
        {16, {35, 36, 37, 45, 46, 47}},
        {17, {40, 41, 42, 48, 49, 50}},
        {18, {42, 43, 44, 50, 51, 52}},
        {19, {44, 45, 46, 52, 53, 54}}};

    std::map<int, std::vector<int>> Board::node_to_adjacentTile = {
        {1, {1}},
        {2, {1}},
        {3, {1, 2}},
        {4, {2}},
        {5, {2, 3}},
        {6, {3}},
        {7, {3}},
        {8, {4}},
        {9, {4, 1}},
        {10, {1, 4, 5}},
        {11, {1, 2, 5}},
        {12, {2, 5, 6}},
        {13, {2, 3, 6}},
        {14, {3, 6, 7}},
        {15, {3, 7}},
        {16, {7}},
        {17, {8}},
        {18, {4, 8}},
        {19, {4, 8, 9}},
        {20, {4, 9, 5}},
        {21, {10, 5, 9}},
        {22, {10, 5, 6}},
        {23, {10, 6, 11}},
        {24, {11, 6, 7}},
        {25, {11, 7, 12}},
        {26, {12, 7}},
        {27, {12}},
        {28, {8}},
        {29, {8, 13}},
        {30, {8, 13, 9}},
        {31, {9, 13, 14}},
        {32, {9, 14, 10}},
        {33, {10, 14, 15}},
        {34, {10, 15, 11}},
        {35, {11, 15, 16}},
        {36, {11, 16, 12}},
        {37, {12, 16}},
        {38, {12}},
        {39, {13}},
        {40, {13, 17}},
        {41, {13, 17, 14}},
        {42, {14, 17, 18}},
        {43, {14, 18, 15}},
        {44, {15, 18, 19}},
        {45, {15, 19, 16}},
        {46, {16, 19}},
        {47, {16}},
        {48, {17}},
        {49, {17}},
        {50, {17, 18}},
        {51, {18}},
        {52, {18, 19}},
        {53, {19}},
        {54, {19}},

    };

    std::map<int, std::vector<int>> Board::node_to_adjacentNode = {
        {1, {2, 9}},
        {2, {1, 3}},
        {3, {2, 4, 11}},
        {4, {3, 5}},
        {5, {4, 6, 13}},
        {6, {5, 7}},
        {7, {6, 15}},
        {8, {9, 18}},
        {9, {8, 10}},
        {10, {9, 11, 20}},
        {11, {10, 12, 3}},
        {12, {11, 13, 22}},
        {13, {12, 14, 5}},
        {14, {13, 15, 24}},
        {15, {14, 16, 7}},
        {16, {15, 26}},
        {17, {18, 28}},
        {18, {17, 19, 8}},
        {19, {18, 20, 30}},
        {20, {19, 21, 10}},
        {21, {20, 22, 32}},
        {22, {21, 23, 12}},
        {23, {22, 24, 34}},
        {24, {23, 25, 14}},
        {25, {24, 26, 36}},
        {26, {25, 27, 16}},
        {27, {26, 38}},
        {28, {29, 17}},
        {29, {28, 30, 39}},
        {30, {29, 31, 19}},
        {31, {30, 32, 41}},
        {32, {31, 33, 21}},
        {33, {32, 34, 43}},
        {34, {33, 35, 23}},
        {35, {34, 36, 45}},
        {36, {35, 37, 25}},
        {37, {36, 38, 47}},
        {38, {37, 27}},
        {39, {40, 29}},
        {40, {39, 41, 48}},
        {41, {40, 42, 31}},
        {42, {41, 43, 50}},
        {43, {42, 44, 33}},
        {44, {43, 45, 52}},
        {45, {44, 46, 35}},
        {46, {45, 47, 54}},
        {47, {46, 37}},
        {48, {49, 40}},
        {49, {48, 50}},
        {50, {49, 51, 42}},
        {51, {50, 52}},
        {52, {51, 53, 44}},
        {53, {52, 54}},
        {54, {53, 46}}};

}