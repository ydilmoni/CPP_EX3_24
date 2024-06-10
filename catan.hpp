#ifndef CATAN_HPP
#define CATAN_HPP
#include <string>
#include <vector>
#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "deck.hpp"

using namespace std;

namespace ariel
{
    class Catan
    {
    private:
    public:
        vector<Player> players;
        Board board;
        Deck dvlpCardDeck = Deck();
        Deck woodDeck = Deck("wood");
        Deck brickDeck = Deck("brick");
        Deck grainDeck = Deck("grain");
        Deck oreDeck = Deck("ore");
        Deck sheepDeck = Deck("wool");

        map<pair<int,int>,Player*> occupiedEdge;
        vector<pair<Player*, string>> occupiedNode;
        Catan(Player &p1, Player& p2, Player &p3);
        Catan();

        void startGame();
        void selectFunction();
        void first2village();
        void putVillageAndRoad(int index);
        void setOccupiedEdge(int start, int end, Player &player);
        vector<pair<int, int>> getUnoccupiedConnectedEdges(int villagePlace) const;
        void initializingOccupiedEdge();
        void printOccupiedEdges() const;
    };

}

#endif // CATAN_HPP