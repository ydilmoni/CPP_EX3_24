#include "board.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <string>

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
            if (landTypes[i] == "desert")//so do a swap
            {
                numbers[findZero(numbers)]=numbers[i];
                numbers[i] = 0;
            }
        }

        for (int i = 0; i < 19; i++)
        {
            setNumAndType(i, numbers[i], landTypes[i]);
        }

    }

    int Board::findZero(vector<int> numbers){
        for (int i =0; i<sizeof(numbers); i++){
            if(numbers[i] == 0){
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
        std::vector<int> rows = {3, 4, 5, 4, 3};
        int index = 0;
        for (int row : rows)
        {
            for (int i = 0; i < 5-row; i++)
            {
                cout<<"      ";
            }
            
            for (int i = 0; i < row; i++)
            {
                cout << tiles[index].getType() << "(" << tiles[index].getNum()<<")";
                if (i < row - 1)
                    std::cout << "   ";
                index++;
            }
            cout << endl;
            cout << endl;
            cout << endl;
        }
    }

    Board::Board()
    {
        initializingTiles();
        printBoard();
    }
}