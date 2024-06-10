#ifndef DECK_HPP
#define DECK_HPP

#include "cardType.hpp"
#include <vector>
#include <stack>
#include <string>
using namespace std;
using namespace ariel;
namespace ariel
{
    class Deck
    {
    public:
        vector<string> cardDeck;
        Deck();
        Deck(string source);
        string drawCard();
        bool isEmpty() const;
        int size = cardDeck.size();
        stack<string> deck;
        void printDeck();

    private:
        void ShuffleCards();
    };
}

#endif // DECK_HPP
