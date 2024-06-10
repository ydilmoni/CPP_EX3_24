#include "catan.hpp"

namespace ariel
{
    Catan::Catan(Player& p1, Player& p2, Player& p3)
    {
        this->players.push_back(p1);
        this->players.push_back(p2);    
        this->players.push_back(p3);
        occupiedNode.resize(54, NULL);
        this->board.printBoard();
    }
    Catan::Catan()
    {
        Player p1("player1");
        Player p2("player2");
        Player p3("player3");
        Catan(p1,p2,p3);
    }
    
}
