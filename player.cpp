#include "player.hpp"
#include <iostream>
namespace ariel
{
    Player::Player(string playerName)
        : name(playerName), score(0), private_score(0), used_road(0), used_village(0),
          used_city(0), public_score(0)
    {

        playerCard["wood"] = 0;
        playerCard["brick"] = 0;
        playerCard["grain"] = 0;
        playerCard["wool"] = 0;
        playerCard["ore"] = 0;
        playerCard["knight"] = 0;
        playerCard["victory_point"] = 0;
        playerCard["build 2 road"] = 0;
        playerCard["year of plenty"] = 0;
        playerCard["monopoly"] = 0;
    }

    Player::Player()
    {
        Player("guest");
    }
    void Player::setName(string newName)
    {
        this->name = newName;
    }

    string Player::getName()
    {
        return this->name;
    }

    void Player::addResurces(string resourceToAdd)
    {
        this->addResurces(resourceToAdd, 1);
    }

    void Player::addResurces(string resourceToAdd, int amount)
    {
        playerCard[resourceToAdd] += amount;
    }

    void Player::removeResurces(string resourceToAdd)
    {
        this->removeResurces(resourceToAdd, 1);
    }

    void Player::removeResurces(string resourceToAdd, int amount)
    {
        playerCard[resourceToAdd] -= amount;
    }

    void Player::trade(Player &other, string iWantToGive, string iWantToGet)
    {
        other.removeResurces(iWantToGet);
        this->addResurces(iWantToGet);
        this->removeResurces(iWantToGive);
        other.addResurces(iWantToGive);
    }

    void Player::build()
    {
        vector<string> myOption = this->iCanbuild();
        if (myOption.size() > 0)
        {
            cout << "You can build: " << endl;
            int i;
            for (i = 0; i < myOption.size(); i++)
            {
                cout<<"(" << to_string(i + 1) << ") "<<myOption[i] << endl;
            }
            cout<<"(" << to_string(i + 1)<< ") Nothing, go back" << endl;
            int whatToBuild;

            cout << "What do you want to build? (choose a number) ";
            cin >> whatToBuild;
            if (whatToBuild > 0 && whatToBuild <= myOption.size()){
                this->build(myOption[whatToBuild - 1]);
            }


        }
        else
        {
            cout << "You can't build anything." << endl;
        }
    }

    void Player::build(string whatToBuild)
    {
        if (whatToBuild == "Road"){
            this->removeResurces("brick");
            this->removeResurces("wood");
            this->addRoad();
        }
        else if (whatToBuild == "Village"){
            this->removeResurces("brick");
            this->removeResurces("wood");
            this->removeResurces("wool");
            this->removeResurces("grain");
            this->addVillage();
        }
        else if (whatToBuild == "City"){
            this->removeResurces("ore", 3);
            this->removeResurces("grain", 2);
            this->addCity();
        }
        else if (whatToBuild == "Buy Development Card"){
            this->removeResurces("ore");
            this->removeResurces("grain");
            this->removeResurces("wool");
            this->buyDevelopmentCard();
        }
        else{};
        
    }

    bool Player::iHave(string cardName)
    {
        if (playerCard[cardName] > 0)
        {
            return true;
        }
        return false;
    }

    bool Player::iHave(string cardName, int amount)
    {
        if (playerCard[cardName] >= amount)
        {
            return true;
        }
        return false;
    }

    vector<string> Player::iCanbuild()
    {
        vector<string> myOption;
        if (this->iHave("wood") && this->iHave("brick"))
        {
            myOption.push_back("Road");
        }

        if (this->iHave("wood") && this->iHave("brick") && this->iHave("grain") && this->iHave("wool"))
        {
            myOption.push_back("Village");
        }

        if (this->iHave("grain", 2) && this->iHave("ore", 3))
        {
            myOption.push_back("City");
        }
        if (this->iHave("grain") && this->iHave("wool") && this->iHave("ore"))
        {
            myOption.push_back("Buy Development Card");
        }

        return myOption;
    }

    void Player::addRoad()
    {
        used_road++;
    }
    void Player::addVillage()
    {
        used_village++;
    }
    void Player::addCity()
    {
        used_city++;
    }
    void Player::buyDevelopmentCard()
    {
    }
    void Player::useDevelopmentCard()
    {
    }
}