#ifndef DECK_HPP
#define DECK_HPP

#include "cardType.hpp"
#include <vector>
#include <stack>
using namespace std;
using namespace ariel;
namespace ariel
{
    class Deck
    {
    public:
        Deck();
        DevelopType drawCard();
        bool isEmpty() const;
        size_t size;
        stack<DevelopType> deck;
        void setStartingDeck(size_t index, DevelopType type);
        void printArray();
        void printDeck();

    private:
        vector<DevelopType> startingStack;
        void initializeDeck();
    };
}

#endif // DECK_HPP
