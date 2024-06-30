// #ifndef DECK_HPP
// #define DECK_HPP

// #include <vector>
// #include <stack>
// #include <string>
// using namespace std;
// namespace ariel
// {
//     class Deck
//     {
//     public:
//         vector<string> cardDeck;
//         Deck();
//         Deck(string source);
//         string drawCard();
//         bool isEmpty() const;
//         int size = cardDeck.size();
//         stack<string> deck;
//         void printDeck();
//         void addToDeck(string card);
//         void addToDeck(string card,int amount);

//     private:
//         void ShuffleCards();
//     };
// }

// #endif // DECK_HPP


#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <stack>
#include <string>
#include <iostream> // For std::cout, std::endl
#include <algorithm> // For std::shuffle
#include <random>    // For std::random_device, std::mt19937
using namespace std;
namespace ariel
{
    class Deck
    {
    public:
        // Constructors
        Deck();            // Default constructor for development card deck
        Deck(string source); // Constructor for other sources card decks

        // Public methods
        string drawCard();       // Draws a card from the deck
        bool isEmpty() const;    // Checks if the deck is empty
        void printDeck();        // Prints all cards in the deck
        void addToDeck(string card);       // Adds a single card to the deck
        void addToDeck(string card, int amount); // Adds multiple cards to the deck
        int size = 0;            // Size of the deck

    private:
        // Private methods
        void ShuffleCards();     // Shuffles the deck

        // Private member variables
        vector<string> cardDeck; // Vector to store cards in the deck
    };
}

#endif // DECK_HPP
