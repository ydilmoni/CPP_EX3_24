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

        void startGame();//first 2 village
        void restOfGame(); //the rest of the game
        void selectFunction();
        void first2village();//loop to make the build rotation
        void putVillageAndRoad(int index); // function to help build vilage and road in the 2 first
        void putVillage(int playerIndex); //build a village in the rest of the game
        void putRoad(int playerIndex); // build a road in the rest of the game

        //node
        void initializingOccupiedNode();  // initializing all the node to nullptr in the start of the game
        void setOccupiedNode(int nodeIndex, Player &player, string buildingType); // Put data into the node vec
        void printNodeInformation() const; // print the occupied node
        

        // edge
        void initializingOccupiedEdge();
        void setOccupiedEdge(int start, int end, Player &player); // Put data into the edges map
        vector<pair<int, int>> getUnoccupiedConnectedEdges(int villagePlace) const; // return all the unoccupied edge the related to "villagePlace"
        void printOccupiedEdges() const; // print the occupied edge
    };

}

#endif // CATAN_HPP