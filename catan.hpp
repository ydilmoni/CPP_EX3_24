#ifndef CATAN_HPP
#define CATAN_HPP
#include <string>
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

        vector<Player*> occupiedNode;
        Catan(Player& p1, Player& p2, Player& p3);
        Catan();
    };

}

#endif // CATAN_HPP