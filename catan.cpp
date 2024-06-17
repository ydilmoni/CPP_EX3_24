#include "catan.hpp"
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#define BLUE "\033[34m"        /* Blue */
#define GREEN "\033[32m"       /* Green */
#define PURPLE "\033[35m"      /* Purple */

namespace ariel
{

    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        this->players.push_back(p1);
        p1.setCollor(BLUE);
        this->players.push_back(p2);
        p2.setCollor(GREEN);
        this->players.push_back(p3);
        p3.setCollor(PURPLE);
        gameNode.resize(54, make_pair(nullptr, ""));
        initializingGameEdges();
        initializingGameNode();

        this->board.printBoard2();
    }

    Catan::Catan()
    {
        Player p1("Player 1");
        Player p2("Player 2");
        Player p3("Player 3");

        *this = Catan(p1, p2, p3);
    }

    void Catan::chackFunction()
    {
        startGame();
        restOfGame();
    }

    void Catan::startGame()
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(players.begin(), players.end(), g);
        cout << "Starting the game, the first player is " << players[0].getName() << endl;
        cout << endl;
        // this_thread::sleep_for(chrono::seconds(5));

        first2village();
    }

    void Catan::first2village()
    {
        cout << "Let's start by placing 2 villages" << endl;
        int i;
        for (i = 0; i < players.size(); i++)
        {
            putVillageAndRoad(i);
        }
        for (int j = 2; j >= 0; j--)
        {
            putVillageAndRoad(j);
        }
    }

    void Catan::putVillageAndRoad(int playerIndex)
    {
        cout << players[playerIndex].getName() << "'s turn" << endl;
        int place;
        vector<int> villageOption = getUnoccupiedNodeVector();
        cout << "Where would you like to build your village?" << endl;
        printVector(villageOption);
        cout << endl
             << endl;
        cout << "Choose location for your tile" << endl;
        cin >> place;

        while (place < 0 || place > 53 || gameNode[place].first != NULL || !canBuildThere(place))
        {
            cout << "You have chosen a place that is already occupied or does not exist because it is not in the range 0-53,\
                 please choose another place"
                 << endl;
            cin >> place;
        }

        setGameNode(place, players[playerIndex], "Village");
        players[playerIndex].addVillage();
        cout << players[playerIndex].getName() << "put a Village in node " << place << endl;

        cout << "Where would you like to build your Road?" << endl;
        vector<pair<int, int>> myOption = getUnoccupiedConnectedEdges(place);

        for (int j = 0; j < myOption.size(); j++)
        {
            cout << "Option " << j << ": Edge between " << myOption[j].first << " and " << myOption[j].second << endl;
        }
        int option;
        cin >> option;
        while (option < 0 || option > myOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        this->setGameEdges(myOption[option].first, myOption[option].second, players[playerIndex]);

        cout << players[playerIndex].getName() << "put a road in " << myOption[option].first << " , " << myOption[option].second << endl;

        this->printAllGameEdges();

        cout << endl;
    }

    void Catan::restOfGame()
    {
        int i = 0;
        bool someoneWin = false;
        while (!someoneWin)
        {
            i = i % 3;
            bool continueMyturn = true;
            cout << "Player " << players[i].getName() << "'s turn" << endl;
            int dice = (rand() % 6 + 1) + (rand() % 6 + 1);
            cout << "You rolled a " << dice << endl;
            dealResurces(dice);

            while (continueMyturn)
            {
                int option;

                cout << "What would you like to do?" << endl;
                cout << "1.   Build" << endl;
                cout << "2.   Trade" << endl;
                cout << "3.   Use a Development Card" << endl;
                cout << "4.   End Turn" << endl;
                cout << "5.   I win" << endl;
                cin >> option;
                while (option < 1 || option > 5)
                {
                    cout << "Invalid option, please choose again" << endl;
                    cin >> option;
                }
                if (option == 1)
                {
                    cout << "Build:" << endl;
                    players[i].build();
                }
                else if (option == 2)
                {
                    cout << "Trade:" << endl;
                }
                else if (option == 3)
                {
                    cout << "Use a Development Card:" << endl;
                }
                else if (option == 4)
                {
                    cout << "End Turn." << endl;
                    continueMyturn = false;
                }
                else if (option == 5)
                {
                    cout << "I win" << endl;
                    continueMyturn = false;
                    someoneWin = true;
                }
            }
            i++;
        }
        cout << "END THE GAME!!" << endl;
    }

    void Catan::selectFunction()
    {
    }

    void Catan::putVillage(int playerIndex)
    {
        int place;
        cout << "Where would you like to build your village?" << endl;
        vector<int> villageOption = getPlaceForVillageByPlayerIndex(playerIndex);
        cin >> place;

        while (place < 1 || place > 54 || gameNode[place].first != NULL)
        {
            cout << "You have chosen a place that is already occupied or does not exist because it is not in the range 1-54,\
                 please choose another place"
                 << endl;
            cin >> place;
        }
        gameNode[place] = make_pair(&players[playerIndex], "Village");
        players[playerIndex].addVillage();
        cout << "Village placed successfully!" << endl;
    }

    void Catan::putRoad(int playerIndex)
    {
        cout << "Choose a place to put a road: " << endl;
        vector<pair<int, int>> roadOption = getPlacesForRoadByPlayerIndex(playerIndex);
        printVector(roadOption);
        int option;
        cin >> option;
        while (option < 0 || option > roadOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        players[playerIndex].addRoad();
        setGameEdges(roadOption[option].first, roadOption[option].second, players[playerIndex]);

        cout << "Road placed successfully!" << endl;
    }

    void Catan::putCity(int playerIndex)
    {
        int place;
        cout << "Where would you like to build your city?" << endl;
        vector<int> cityOption = getPlaceForCityByPlayerIndex(playerIndex);
        printVector(cityOption);
        cin >> place;
        while (place < 0 || place > cityOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> place;
        }
        gameNode[cityOption[place]] = make_pair(&players[playerIndex], "City");
        players[playerIndex].addCity();
        cout << "City placed successfully!" << endl;
    }

    void Catan::initializingGameNode()
    {
        for (int i = 0; i < 54; i++)
        {
            gameNode.push_back(make_pair(nullptr, ""));
        }
    }

    void Catan::setGameNode(int nodeIndex, Player &player, string buildingType)
    {
        gameNode[nodeIndex] = make_pair(&player, buildingType);
    }

    void Catan::printAllNodeInformation() const
    {
        for (int i = 0; i < 54; i++)
        {
            if (gameNode[i].first != nullptr)
            {
                cout << "Node " << i << " is occupied by " << gameNode[i].first->getName() << " with a " << gameNode[i].second << endl;
            }
            else
            {
                cout << "Node " << i << " is not occupied" << endl;
            }
        }
    }

    vector<int> Catan::getUnoccupiedNodeVector()
    {
        vector<int> unoccupiedNode;
        for (int i = 0; i < 54; i++)
        {
            if (canBuildThere(i))
            {
                unoccupiedNode.push_back(i);
            }
        }
        return unoccupiedNode;
    }

    bool Catan::canBuildThere(int nodeIndex)
    {
        bool result = false;
        if (gameNode[nodeIndex].first != nullptr)
        {
            return false;
        }
        for (const auto &[key, values] : Board::node_to_adjacentNode)
        {
            if (key == nodeIndex)
            {
                for (int i = 0; i < values.size(); i++)
                {
                    if (gameNode[values[i]].first != nullptr)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void Catan::setGameEdges(int start, int end, Player &player)
    {
        this->gameEdges[{start, end}] = &player;
        this->gameEdges[{end, start}] = &player;
    }

    vector<pair<int, int>> Catan::getUnoccupiedConnectedEdges(int node) const
    {
        vector<pair<int, int>> unoccupiedEdges;
        for (const auto &[edge, player] : gameEdges)
        {
            if (player == nullptr && (edge.first == node || edge.second == node))
            {
                unoccupiedEdges.push_back(edge);
            }
        }
        return unoccupiedEdges;
    }

    void Catan::initializingGameEdges()
    {
        for (const auto &[key, values] : Board::node_to_adjacentNode)
        {
            for (int value : values)
            {
                if (key < value)
                {
                    gameEdges[{key, value}] = nullptr;
                }
            }
        }
    }

    void Catan::printAllGameEdges() const
    {
        for (const auto &[edge, player] : gameEdges)
        {
            if (edge.first < edge.second)
            {
                cout << "(" << edge.first << ", " << edge.second << ")";
                if (player)
                {
                    cout << " - Controlled by: " << player->getName();
                }
                cout << endl;
            }
        }
    }

    void Catan::printUnoccupiedEdge() const
    {
        for (const auto &[edge, player] : gameEdges)
        {
            if (!player)
            {
                cout << "(" << edge.first << ", " << edge.second << ")";
            }
        }
    }

    vector<pair<int, int>> Catan::getPlacesForRoadByPlayerIndex(int playerIndex)
    {
        vector<pair<int, int>> placesForRoad;
        for (const auto &[edge, player] : gameEdges)
        {
            if (player && player == &players[playerIndex])
            {
                for (int node : Board::node_to_adjacentNode[edge.first])
                {
                    if (gameEdges[make_pair(edge.first, node)] == nullptr)
                    {
                        placesForRoad.push_back({edge.first, node});
                        placesForRoad.push_back({node, edge.first});
                    }
                }
            }
        }
        return placesForRoad;
    }

    vector<int> Catan::getPlaceForCityByPlayerIndex(int playerIndex)
    {
        vector<int> placesForCity;
        for (int i = 0; i < gameNode.size(); i++)
        {
            if (gameNode[i].first == &players[playerIndex] && gameNode[i].second == "Village")
            {
                placesForCity.push_back(i);
            }
        }
        return placesForCity;
    }

    vector<int> Catan::getPlaceForVillageByPlayerIndex(int playerIndex)
    {
        vector<int> placesForVillage;
        for (int i = 0; i < gameNode.size(); i++)
        {
            if (gameNode[i].first == nullptr)
            {
                vector<int> adjacentNode = Board::node_to_adjacentNode[i];
                bool canBuild = true;
                for (int node : adjacentNode)
                {
                    if (gameNode[node].first != nullptr)
                    {
                        canBuild = false;
                    }
                }
                if (canBuild)
                {
                    placesForVillage.push_back(i);
                }
            }
        }
        return placesForVillage;
    }

    void Catan::dealResurces(int number)
    {
        for (Tile t : this->board.tiles)
        {
            if (t.number == number)
            {
                for (const auto &[key, values] : Board::tileLocation_to_adjacentNode)
                {
                    if (t.tile_location == key)
                    {
                        for (int node : values)
                        {
                            if (gameNode[node].first != nullptr)
                            {
                                gameNode[node].first->addResurces(t.landType);
                            }
                        }
                    }
                }
            }
        }
    }

    void Catan::printOptionFromVector(vector<int> &vec) const
    {
        for (int i = 0; i < vec.size(); i++)
        {
            cout << "(option " << i << ") " << vec[i] << endl;
        }
    }

    ostream &operator<<(ostream &os, pair<int, int> edge)
    {
        os << edge.first << ", " << edge.second << endl;
        return os;
    }

    ostream &operator<<(ostream &os, const pair<ariel::Player *, string> &p)
    {
        os << "(Player: " << p.first << ", String: " << p.second << ")";
        return os;
    }
}
