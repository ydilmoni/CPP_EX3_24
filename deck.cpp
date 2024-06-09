

#include "deck.hpp"
#include <thread>
#include <random>
#include <iostream>

#define NUM_OF_KNIGHT 14
#define NUM_OF_VP 4
#define NUM_OF_OTHER 2
#define NUM_OF_DVL_CARD NUM_OF_KNIGHT + NUM_OF_VP + (NUM_OF_OTHER * 3)

namespace ariel
{
    Deck::Deck()
    {
        initializeDeck();
    }

    void Deck::initializeDeck()
    {
        startingStack = {NUM_OF_DVL_CARD, none};
        size = 0;
        size_t i;

        for (i = 0; i < NUM_OF_KNIGHT; i++)
        {
            setStartingDeck(i, knight);
            // cout<<"startingStack["<<i<<"] =" << startingStack[i]<<endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        for (i; i < NUM_OF_KNIGHT + NUM_OF_VP; i++)
        {
            setStartingDeck(i, victory_point);
            // cout<<"startingStack["<<i<<"] =" << startingStack[i]<<endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        for (i; i < NUM_OF_DVL_CARD; i++)
        {

            setStartingDeck(i, road_building);
            // cout<<"startingStack["<<i<<"] =" << startingStack[i]<<endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            i++;
            setStartingDeck(i, monopoly);
            // cout<<"startingStack["<<i<<"] =" << startingStack[i]<<endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
            i++;
            setStartingDeck(i, year_of_plenty);
            // cout<<"startingStack["<<i<<"] =" << startingStack[i]<<endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        // cout<<"size = "<<size<<endl;

        // cout << NUM_OF_DVL_CARD<<endl;
        // std::this_thread::sleep_for(std::chrono::seconds(5));
        while (size < NUM_OF_DVL_CARD - 1)
        {
            int num = NUM_OF_DVL_CARD;
            size_t n = rand() % num;
            // cout<<"startingStack[" << n<<"] = "<<startingStack[n]<<endl;
            if (startingStack[n] != none)
            {
                deck.push(startingStack[n]);
                setStartingDeck(n, none);
                size++;
                // cout<<"size = "<<size<<endl;
                // if (size % 5 ==0){
                //     printArray();
                // }
                // std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        cout << "DONE!!!" << endl;
        printDeck();
    }

    DevelopType Deck::drawCard()
    {
        if (isEmpty())
        {
            cout << "No more cards to draw" << endl;
            return none;
        }

        DevelopType card = deck.top();
        deck.pop();
        return card;
    }

    bool Deck::isEmpty() const
    {
        return size == 0;
    }
    void Deck::setStartingDeck(size_t index, DevelopType type)
    {
        startingStack[index] = type;
    }

    void Deck::printArray()
    {
        for (size_t i = 0; i < NUM_OF_DVL_CARD; i++)
        {
            cout << startingStack[i] << ", ";
        }
        cout << endl;
    }

    void Deck::printDeck()
    {
        while (!isEmpty())
        {
            DevelopType card = deck.top();
            deck.pop();
            cout << card << endl;
            --size;
        }
    }
}
