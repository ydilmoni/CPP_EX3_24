#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

namespace ariel
{
    class Player
    {
    private:
        int score;
        int private_score;
        map<string, int> playerCard;

    public:
        string name;
        int used_road;
        int used_village;
        int used_city;
        int public_score;

        Player(string name);
        Player();
        void setName(string newName);
        string getName();
        void addResurces(string resourceToAdd);
        void addResurces(string resourceToAdd, int amount);
        void removeResurces(string resourceToAdd);
        void removeResurces(string resourceToAdd, int amount);
        void trade(Player &other, string iWantToGive, string iWantToGet);
        void build();
        void build(string whatToBuild);
        bool iHave(string cardName);
        bool iHave(string cardName, int amount);
        vector<string>iCanBuild();
        void addRoad();
        void addVillage();
        void addCity();
        void buyDevelopmentCard();
        void useDevelopmentCard();
    };

}
#endif // PLAYER_HPP