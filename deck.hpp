#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <stack>
#include <string>
using namespace std;
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
        void addToDeck(string card);
        void addToDeck(string card,int amount);

    private:
        void ShuffleCards();
    };
}

#endif // DECK_HPP
