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
        initializingOccupiedNode();

        this->board.printBoard();
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
    
    void Catan::restOfGame(){
        bool someoneWin = false;
        while (!someoneWin){
            for (Player &p : players){
                
            }
        }
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
        printNodeInformation();
        cin >> place;

        while (place < 1 || place > 54 || occupiedNode[place - 1].first != NULL)
        {
            cout << "You have chosen a place that is already occupied or does not exist because it is not in the range 1-54,\
                 please choose another place"<< endl;
            cin >> place;
        }
        setOccupiedNode(place-1, players[i], "Village");
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

    void Catan::putVillage(int playerIndex)
    {
        int place;
        cout << "Where would you like to build your village? (1-54)" << endl;
        
        cin >> place;

        while (place < 1 || place > 54 || occupiedNode[place - 1].first != NULL)
        {
            cout << "You have chosen a place that is already occupied or does not exist because it is not in the range 1-54,\
                 please choose another place"<< endl;
            cin >> place;
        }
        occupiedNode[place - 1] = make_pair(&players[playerIndex], "Village");
        players[playerIndex].addVillage();
        cout << "Village placed successfully!" << endl;
    }

    void Catan::initializingOccupiedNode()
    {
        for (int i = 0; i < 54; i++){
            occupiedNode.push_back(make_pair(nullptr, ""));
        }
    }

    void Catan::setOccupiedNode(int nodeIndex, Player &player, string buildingType)
    {
        occupiedNode[nodeIndex] = make_pair(&player, buildingType);
    }

    void Catan::printNodeInformation() const
    {
        for (int i = 0; i < 54; i++)
        {
            if (occupiedNode[i].first != nullptr)
            {
                cout << "Node " << i + 1 << " is occupied by " << occupiedNode
                [i].first->getName() << " with a " << occupiedNode[i].second <<
                endl;
            }
            else
            {
                cout << "Node " << i + 1 << " is not occupied" << endl;
            }   
        }
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
