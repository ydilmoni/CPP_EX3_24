#include "catan.hpp"
#include <random>
#include <algorithm>

namespace ariel
{

    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        this->players.push_back(p1);
        this->players.push_back(p2);
        this->players.push_back(p3);
        occupiedNode.resize(54, make_pair(nullptr, ""));
        initializingOccupiedEdge();

        this->board.printBoard2();
    }

    Catan::Catan()
    {
        Player p1("Player 1");
        Player p2("Player 2");
        Player p3("Player 3");

        *this = Catan(p1, p2, p3);
    }

    void Catan::startGame()
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(players.begin(), players.end(), g);
        cout << "Starting the game, the first player is " << players[0].getName() << endl;
        cout << endl;

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
        for (int j=2; j>=0 ; j--)
        {
            putVillageAndRoad(j);
        }

    }

    void Catan::putVillageAndRoad(int i)
    {
        cout << players[i].getName() << "'s turn" << endl;
        int place;
        cout << "Where would you like to build your first village? (1-54)" << endl;
        cin >> place;

        while (place < 1 || place > 54 || occupiedNode[place - 1].first != NULL)
        {
            cout << "You have chosen a place that is already occupied or does not exist because it is not in the range 1-54,\
                 please choose another place"
                 << endl;
            cin >> place;
        }
        occupiedNode[place - 1] = make_pair(&players[i], "Village");
        players[i].addVillage();
        cout << "Village placed successfully!" << endl;

        cout << "Where would you like to build your first Road?" << endl;
        vector<pair<int, int>> myOption = getUnoccupiedConnectedEdges(place);

        for (int j = 0; j < myOption.size(); j++)
        {
            cout << "Option " << j << ": Edge between " << myOption[j].first << " and " << myOption[j].second << endl;
        }
        int option;
        cin >> option;
        while (option < 0 || option > myOption.size())
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        this->setOccupiedEdge(myOption[option].first, myOption[option].second, players[i]);

        cout << "Road placed successfully!" << endl;

        this->printOccupiedEdges();

        cout << endl;
    }

    void Catan::setOccupiedEdge(int start, int end, Player &player)
    {
        this->occupiedEdge[{start, end}] = &player;
        this->occupiedEdge[{end, start}] = &player;
    }

    vector<pair<int, int>> Catan::getUnoccupiedConnectedEdges(int node) const
    {
        vector<pair<int, int>> unoccupiedEdges;
        for (const auto &[edge, player] : occupiedEdge)
        {
            if (player == nullptr && (edge.first == node || edge.second == node))
            {
                unoccupiedEdges.push_back(edge);
            }
        }
        return unoccupiedEdges;
    }

    void Catan::initializingOccupiedEdge()
    {
        for (const auto &[key, values] : Board::node_to_adjacentNode)
        {
            for (int value : values)
            {
                occupiedEdge[{key, value}] = nullptr;
            }
        }
    }

    void Catan::printOccupiedEdges() const
    {
        for (const auto &[edge, player] : occupiedEdge)
        {
            std::cout << "(" << edge.first << ", " << edge.second << ")";
            if (player)
            {
                std::cout << " - Controlled by: " << player->getName();
            }
            std::cout << std::endl;
        }
    }

}
