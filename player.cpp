#include "player.hpp"
namespace ariel{
    Player::Player(string playerName)
        : name(playerName), score(0), private_score(0), used_road(0), used_village(0),
            used_city(0), public_score(0){

        resources[wood] = 0;
        resources[brick] = 0;
        resources[grain] = 0;
        resources[wool] = 0;
        resources[ore] = 0;
    }

    Player::~Player()
    {
    }
    void Player::buyDvlpCard()
    {
        if (resources[wool] >= 1 && resources[ore] >= 1 && resources[grain] >= 1){
            
        }
    }
}