#ifndef PLAYER_HPP
#define PLAYER_HPP



#include "cardType.hpp"
#include <string>
#include <map>

using namespace std;
using namespace ariel;

namespace ariel{
    class Player{
    private:
        int score;
        int private_score;
        map<ResourceType, int> resources;
        


    public:
        string name;
        int used_road;
        int used_village;
        int used_city;
        int public_score;

        Player(string name);
        ~Player();
        void buyDvlpCard();
        void buildCity();
        void buildVillage();
        void buildRoad();
        bool nextPlayer();
        bool tenPoint();
    };

}
#endif //PLAYER_HPP