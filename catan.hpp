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
        vector<reference_wrapper<Player>> players;
        Board board;
        map<string,Deck> decks;

        map<pair<int, int>, Player *> gameEdges;
        vector<pair<Player *, string>> gameNode;
        Catan(Player &p1, Player &p2, Player &p3);
        Catan();

        // First 2 village and road:
        void startGame();                  // First 2 village.
        void first2village();              // Loop to make the first two village build rotation.
        void putVillageAndRoad(int index); // Function to help build the fiest 2 vilage and road.
        void buildFreeRoad(int playerIndex, int place);

        // Rest of the game:
        void restOfGame(); // Rest of the game.
        void iCanBuild(int playerIndex);  // check if i can build
        void putVillage(int playerIndex); // Build a village in the rest of the game.
        void putRoad(int playerIndex);    // Build a road in the rest of the game.
        void putCity(int playerIndex);
        void trade(int playerIndex);
        void buyDevelopmentCard(int playerIndex);
        void chooseDevelopmentCard(int playerIndex);
        void useDevelopmentCard(string card, int playerIndex);
        void useRoadBuilding(int playerIndex);
        void useMonopoly(int playerIndex);
        void useYearOfPlenty(int playerIndex);
        void returnCardToDeck(string card, int amount);
        void returnCardToDeck(string card);

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
        void printVector(vector<string> &vec)const;
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

        string p(int tileNum);                               // print tile information in the collor
        string pr(int start, int end, string whatToPrint);   // print the road collor (use for diagonals)
        string pr(int start, int end);                       // print the road collor
        string p2(int nodeNum);                              // print node num in coolor and [] {} ()
        string d1(int start, int end);                       // d1 is /
        string d2(int start, int end);                       // d for diagonal d2 is '\'
        string m(int start, int end);                        // m for middle
        string ms(int amount, int firstStart, int firstEnd); // ms for middles , st - for startType

        void printBoard2();
    };
    std::string operator*(const std::string &s, int n);
    std::string operator*(int n, const std::string &s);

}

#endif // CATAN_HPP