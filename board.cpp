#include "board.hpp"


#define RESET "\033[0m"
#define RED "\033[31m"         /* Red */
#define BLACK "\033[30m"       /* Black */
#define YELLOW "\033[33m"      /* Yellow */
#define WHITE "\033[37m"       /* White */
#define BROWN "\033[38;5;130m" /* Brown */
#define CAMEL "\033[38;5;180m" /* Camel */

using namespace std;

namespace ariel
{
    void Board::initializingTiles()
    {
        tiles.resize(19);
        for (int i = 0; i < 19; i++)
        {
            tiles[i] = Tile(i);
        }
        vector<string> landTypes = {
            "W", "W", "W", "W",
            "B", "B", "B",
            "G", "G", "G", "G",
            "S", "S", "S", "S",
            "O", "O", "O",
            "D"};

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
            if (landTypes[i] == "D") // so do a swap
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
                if (tiles[index].getType() == "W")
                {
                    cout << BROWN << setw(5) << tiles[index].getType() << "(" << tiles[index].getNum() << ")" << RESET;
                }
                else if (tiles[index].getType() == "B")
                {
                    cout << RED << setw(5) << tiles[index].getType() << "(" << tiles[index].getNum() << ")" << RESET;
                }
                else if (tiles[index].getType() == "G")
                {
                    cout << YELLOW << setw(5) << tiles[index].getType() << "(" << tiles[index].getNum() << ")" << RESET;
                }
                else if (tiles[index].getType() == "S")
                {
                    cout << WHITE << setw(5) << tiles[index].getType() << "(" << tiles[index].getNum() << ")" << RESET;
                }
                else if (tiles[index].getType() == "O")
                {
                    cout << BLACK << setw(5) << tiles[index].getType() << "(" << tiles[index].getNum() << ")" << RESET;
                }
                else if (tiles[index].getType() == "D")
                {
                    cout << CAMEL << setw(5) << tiles[index].getType() << "(" << tiles[index].getNum() << ")" << RESET;
                }

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

    void Board::printBoard2()
    {
        string output = "";
        output += "                                                                       \n";
        output += "                                [0]-(0)-[1]                              \n";
        output += "                                /         \\                              \n";
        output += "                              (1)         (2)                              \n";
        output += "                              /             \\                              \n";
        output += "                    [2]-(0)-[3]     " +p(0)+ "      [4]-(0)-[5]   \n" ;
        output += "                   /          \\             /          \\                                       \n";
        output += "                 (0)          (0)         (0)          (0)                              \n";
        output += "                 /              \\         /              \\                           \n";
        output += "      [6]-(0)-[7]      " +p(1)+ "       [8]-(0)-[9]      " +p(2)+ "     [10]-(0)-[11]                              \n";
        output += "      /          \\             /          \\             /          \\                                       \n";
        output += "    (0)          (0)         (0)          (0)         (0)          (0)                             \n";
        output += "    /              \\         /              \\         /              \\                            \n";
        output += "  [12]     " +p(3)+ "    [13]-(0)-[14]     " +p(4)+ "     [15]-(0)-[16]      " +p(5)+ "     [17]                                   \n";
        output += "    \\             /          \\             /          \\              /                                        \n";
        output += "    (0)         (0)          (0)         (0)          (0)          (0)                              \n";
        output += "      \\         /              \\         /              \\          /                            \n";
        output += "     [18]-(0)-[19]     " +p(6)+ "    [20]-(0)-[21]     " +p(7)+ "     [22]-(0)-[23]                                   \n";
        output += "      /          \\             /          \\             /          \\                                        \n";
        output += "    (0)          (0)         (0)          (0)         (0)          (0)                              \n";
        output += "    /              \\         /              \\         /              \\                            \n";
        output += "  [24]    " +p(8)+ "     [25]-(0)-[26]      " +p(9)+ "     [27]-(0)-[28]     " +p(10)+ "     [29]                                   \n";
        output += "    \\             /          \\             /          \\              /                                       \n";
        output += "    (0)         (0)          (0)         (0)          (0)          (0)                              \n";
        output += "      \\         /              \\         /              \\          /                            \n";
        output += "     [30]-(0)-[31]     " +p(11)+ "     [32]-(0)-[33]     " +p(12)+ "     [34]-(0)-[35]                                    \n";
        output += "      /          \\             /          \\             /          \\                                       \n";
        output += "    (0)          (0)         (0)          (0)         (0)          (0)                              \n";
        output += "    /              \\         /              \\         /              \\                            \n";
        output += "  [36]     " +p(13)+ "     [37]-(0)-[38]     " +p(14)+ "     [39]-(0)-[40]     " +p(15)+ "     [41]                              \n";
        output += "    \\             /          \\             /          \\              /                                        \n";
        output += "    (0)         (0)          (0)         (0)          (0)          (0)                             \n";
        output += "      \\         /              \\         /              \\          /                           \n";
        output += "     [42]-(0)-[43]     " +p(16)+ "     [44]-(0)-[45]     " +p(17)+ "      [46]-(0)-[47]                                    \n";
        output += "                 \\             /          \\             /                                                 \n";
        output += "                 (0)         (0)          (0)         (0)                           \n";
        output += "                   \\         /              \\         /                                 \n";
        output += "                  [48]-(0)-[49]     " +p(18)+ "     [50]-(0)-[51]                                         \n";
        output += "                              \\             /                                            \n";
        output += "                              (0)         (0)                                  \n";
        output += "                                \\         /                                   \n";
        output += "                               [52]-(0)-[53]                                          \n";

        
        cout<<"rint the board"<<endl;
        cout<<output<<endl;
    }

    Board::Board()
    {
        initializingTiles();
    }

    string Board::p(int tileNum)
    {
        string result = string(this->tiles[tileNum].collor) + this->tiles[tileNum].getType() + string(this->tiles[tileNum].collor) +to_string(this->tiles[tileNum].getNum())  + string(RESET); 
        return result;
    }

    string Board::pr(int start, int end, string whatToPrint){
        map<pair<int, int>, Player *> map = Catan::gameEdges; 
        string result;
        string collor = RESET;
        for (const auto &[edge, player] : map)
        {
            if (edge.first == start && edge.second == end && player!= nullptr) 
            {
                collor = player->collor;
            }
        }
        result = string(collor)+whatToPrint+string(RESET); 
        return result;
    }

    std::map<int, std::vector<int>> Board::tileLocation_to_adjacentNode ={
        {0,{0,1,4,9,8,3}},
        {1,{2,3,8,14,13,7}},
        {2,{4,5,9,10,15,16}},
        {3,{6,7,13,19,18,12}},
        {4,{8,9,15,21,20,14}},
        {5,{10,11,16,22,23,17}},
        {6,{13,14,20,26,25,19}},
        {7,{15,16,21,27,28,22}},
        {8,{18,19,24,25,30,31}},
        {9,{20,21,26,32,33,27}},
        {10,{22,23,28,34,35,29}},
        {11,{25,26,31,32,37,38}},
        {12,{27,28,33,34,39,40}},
        {13,{30,31,36,43,42,37}},
        {14,{32,33,38,44,45,39}},
        {15,{34,35,40,46,47,41}},
        {16,{38,37,44,48,49,43}},
        {17,{39,40,45,50,51,46}},
        {18,{44,45,49,50,52,53}}
        };

    std::map<int, std::vector<int>> Board::node_to_adjacentTile = {
        {0,{0}},
        {1,{0}},
        {2,{1}},
        {3,{1,0}},
        {4,{2,0}},
        {5,{2}},
        {6,{3}},
        {7,{3,1}},
        {8,{4,1,0}},
        {9,{4,2,0}},
        {10,{5,2}},
        {11,{5}},
        {12,{3}},
        {13,{6,3,1}},
        {14,{6,4,1}},
        {15,{7,4,2}},
        {16,{7,5,2}},
        {17,{5}},
        {18,{8,3}},
        {19,{8,6,3}},
        {20,{9,4,6}},
        {21,{9,7,4}},
        {22,{10,5,7}},
        {23,{10,5}},
        {24,{8}},
        {25,{11,6,8}},
        {26,{11,9,6}},
        {27,{12,7,9}},
        {28,{12,10,7}},
        {29,{10}},
        {30,{13,8}},
        {31,{13,11,8}},
        {32,{14,9,11}},
        {33,{14,12,9}},
        {34,{12,10,15}},
        {35,{15,10}},
        {36,{13}},
        {37,{16,11,13}},
        {38,{16,14,11}},
        {39,{17,12,14}},
        {40,{17,15,12}},
        {41,{15}},
        {42,{13}},
        {43,{16,13}},
        {44,{18,14,16}},
        {45,{18,17,14}},
        {46,{15,17}},
        {47,{15}},
        {48,{16}},
        {49,{16,18}},
        {50,{17,18}},
        {51,{17}},
        {52,{18}},
        {53,{18}}
    };

    std::map<int, std::vector<int>> Board::node_to_adjacentNode = {
        {0, {1,3}},
        {1, {4, 0}},
        {2,{3,7}},
        {3, {0,2,8}},
        {4, {1,5,9}},
        {5, {4,10}},
        {6, {7,12}},
        {7, {2,6,13}},
        {8, {3,9,14}},
        {9, {4,8,15}},
        {10, {5,11,16}},
        {11, {10,17}},
        {12, {6,18}},
        {13, {7,14,19}},
        {14, {8,13,20}},
        {15, {9,16,21}},
        {16, {10,15,22}},
        {17, {11,23}},
        {18, {12,24,19}},
        {19, {13,18,25}},
        {20, {14,26,21}},
        {21, {15,20,27}},
        {22, {16,28,23}},
        {23, {17,29}},
        {24, {18,30}},
        {25, {19,26,31}},
        {26, {20,25,32}},
        {27, {21,33,28}},
        {28, {22,27,34}},
        {29, {23,35}},
        {30, {24,36,31}},
        {31, {25,30,37}},
        {32, {26,38,33}},
        {33, {27,32,39}},
        {34, {28,40,35}},
        {35, {29,41}},
        {36, {30,42}},
        {37, {31,43,38}},
        {38, {32,37,44}},
        {39, {33,45,40}},
        {40, {34,46,39}},
        {41, {35,47}},
        {42, {36,43}},
        {43, {37,42,48}},
        {44, {38,49,45}},
        {45, {39,44,50}},
        {46, {40,51,47}},
        {47, {41,46}},
        {48, {43,59}},
        {49, {44,52,48}},
        {50, {45,53,51}},
        {51, {46,50}},
        {52, {49,53}},
        {53, {50,52}}
        };

}