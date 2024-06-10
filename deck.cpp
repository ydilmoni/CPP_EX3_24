

#include "deck.hpp"
#include <thread>
#include <random>
#include <iostream>
#include <algorithm>

namespace ariel
{

    Deck::Deck()  // Development card deck
    {

        for (int i = 0; i < 19; i++)
        {
            cardDeck.push_back("knight");
        }
        for (int i = 0; i < 4; i++)
        {
            cardDeck.push_back("victory point");
        }
        for (int i = 0; i < 2; i++)
        {
            cardDeck.push_back("build 2 road");
        }
        for (int i = 0; i < 2; i++)
        {
            cardDeck.push_back("year of plenty");
        }
        for (int i = 0; i < 2; i++)
        {
            cardDeck.push_back("monopoly");
        }
        ShuffleCards();
    }

    Deck::Deck(string source)  // Sources card decks
    {
        for (int i = 0; i < 19; i++)
        {
            cardDeck.push_back(source);
        }
    }

    void Deck::ShuffleCards() // this function from chatGPT
    {

        random_device rd;
        mt19937 g(rd());
        shuffle(cardDeck.begin(), cardDeck.end(), g);

    }

    string Deck::drawCard()
    {
        if (isEmpty())
        {
            cout << "No more cards to draw" << endl;
            return NULL;
        }

        string card = cardDeck.back();
        cardDeck.pop_back();
        size--;
        return card;
    }

    bool Deck::isEmpty() const
    {
        return size == 0;
    }

    void Deck::printDeck()
    {
        for (size_t i = 0; i < cardDeck.size(); i++)
        {
            cout << cardDeck[i] << endl;
        }
    }
}
