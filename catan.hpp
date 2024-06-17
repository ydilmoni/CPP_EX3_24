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

        static map<pair<int, int>, Player *> gameEdges;
        vector<pair<Player *, string>> gameNode;
        Catan(Player &p1, Player &p2, Player &p3);
        Catan();

        // First 2 village and road:
        void startGame();                  // First 2 village.
        void first2village();              // Loop to make the first two village build rotation.
        void putVillageAndRoad(int index); // Function to help build the fiest 2 vilage and road.

        // Rest of the game:
        void restOfGame(); // Rest of the game.
        void selectFunction();
        void putVillage(int playerIndex); // Build a village in the rest of the game.
        void putRoad(int playerIndex);    // Build a road in the rest of the game.
        void putCity(int playerIndex);

        // node
        void initializingGameNode();                                          // initializing all the node to nullptr in the start of the game
        void setGameNode(int nodeIndex, Player &player, string buildingType); // Put data into the node vec
        void printAllNodeInformation() const;                                 // print the gameNode member
        vector<int> getUnoccupiedNodeVector();                                // return all the node that i can build there
        bool canBuildThere(int nodeIndex);                                    // return true if i can build on node nodeIndex

        // edge
        void initializingGameEdges();
        void setGameEdges(int start, int end, Player &player);                      // Put data into the edges map
        vector<pair<int, int>> getUnoccupiedConnectedEdges(int villagePlace) const; // return all the unoccupied edge related to "villagePlace"
        void printAllGameEdges() const;                                             // print all edge
        void printUnoccupiedEdge() const;
        vector<pair<int, int>> getPlacesForRoadByPlayerIndex(int playerIndex); // get player index and return all the places that he can build a road
        vector<int> getPlaceForCityByPlayerIndex(int playerIndex);
        vector<int> getPlaceForVillageByPlayerIndex(int playerIndex);

        // Tiles
        void dealResurces(int number); // every player near this number get the match resurce

        // Print:
        void printOptionFromVector(vector<int> &vec) const;

        void printVector(vector<int> &vec)
        {
            for (int i = 0; i < vec.size(); i++)
            {
                cout << vec[i] << endl;
            }
        }
        void printVector(vector<pair<int, int>> &vec)
        {
            for (size_t i = 0; i < vec.size(); i++)
            {
                cout << "(option " << i << ") " << vec[i].first << " " << vec[i].second << endl;
            }
        }

        void printVector(vector<pair<Player *, string>> &vec)
        {
            for (size_t i = 0; i < vec.size(); i++)
            {
                cout << "(Node " << i << ") " << vec[i].first->getName() << " build a" << vec[i].second << endl;
            }
        }

        void chackFunction();
    };

}

#endif // CATAN_HPP