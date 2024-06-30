#include "player.hpp"
#include <iostream>
namespace ariel
{
    Player::Player(string playerName)
        : name(playerName), score(0), private_score(0), used_road(0), used_village(0),
          used_city(0), public_score(0), usedKnight(0), numOfResource(0)
    {

        playerCard["B"] = 0;
        playerCard["W"] = 0;
        playerCard["S"] = 0;
        playerCard["G"] = 0;
        playerCard["O"] = 0;
        playerCard["knight"] = 0;
        playerCard["victory point"] = 0;
        playerCard["build 2 road"] = 0;
        playerCard["year of plenty"] = 0;
        playerCard["monopoly"] = 0;
    }

    Player::Player()
    {
        Player("guest");
    }
    string Player::getCollor() const
    {
        return this->collor;
    }
    void Player::addPrivateScore()
    {
        private_score++;
    }
    void Player::setCollor(string newCollor)
    {
        this->collor = newCollor;
    }
    void Player::setName(string newName)
    {
        this->name = newName;
    }

    string Player::getName() const
    {
        return this->name;
    }

    void Player::addResurces(string resourceToAdd)
    {
        this->addResurces(resourceToAdd, 1);
        cout << this->getName() << " got " << resourceToAdd << endl;
    }

    void Player::addResurces(string resourceToAdd, int amount)
    {
        playerCard[resourceToAdd] += amount;
        if (!(resourceToAdd == "knight" || resourceToAdd == "victory point" || resourceToAdd == "build 2 road" || resourceToAdd == "year of plenty" || resourceToAdd == "monopoly"))
        {
            this->numOfResource += amount;
        }
    }

    void Player::removeResurces(string resourceToRemove)
    {
        this->removeResurces(resourceToRemove, 1);
    }

    void Player::removeResurces(string resourceToRemove, int amount)
    {
        playerCard[resourceToRemove] -= amount;
        if (!(resourceToRemove == "knight" || resourceToRemove == "victory point" || resourceToRemove == "build 2 road" || resourceToRemove == "year of plenty" || resourceToRemove == "monopoly"))
        {
            this->numOfResource -= amount;
        }
    }

    void Player::build()
    {
        vector<string> myOption = this->iCanBuild();
        myOption.push_back("Nothing, go back");

        cout << "You can build: " << endl;
        int i;
        for (i = 0; i < myOption.size(); i++)
        {
            cout << "(" << to_string(i) << ") " << myOption[i] << endl;
        }

        int whatToBuild;

        cout << "What do you want to build? (choose a number) ";
        cin >> whatToBuild;
        if (whatToBuild > 0 && whatToBuild < myOption.size() - 1)
        {
            this->build(myOption[whatToBuild]);
        }
    }

    void Player::build(string whatToBuild)
    {
        if (whatToBuild == "Road")
        {
            this->removeResurces("B");
            this->removeResurces("W");
            this->addRoad();
        }
        else if (whatToBuild == "Village")
        {
            this->removeResurces("B");
            this->removeResurces("W");
            this->removeResurces("S");
            this->removeResurces("G");
            this->addVillage();
        }
        else if (whatToBuild == "City")
        {
            this->removeResurces("G", 2);
            this->removeResurces("O", 3);
            this->addCity();
        }
        else if (whatToBuild == "Buy Development Card")
        {
            this->removeResurces("S");
            this->removeResurces("G");
            this->removeResurces("O");
            // this->buyDevelopmentCard();
        }
        else if (whatToBuild == "freeRoad")
        {
            this->addRoad();
        }
        else
        {
        };
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

    bool Player::iCanBuild(string building)
    {
        if (building == "Road" && iHave("B") & iHave("W"))
        {
            return true;
        }

        if (building == "Village" && iHave("B") && iHave("W") && iHave("G") && iHave("S"))
        {
            return true;
        }

        if (building == "City" && iHave("G", 2) && iHave("O", 3))
        {
            return true;
        }
        if (building == "Buy Development Card" && iHave("O") && iHave("G") && iHave("S"))
        {
            return true;
        }
        return false;
    }

    vector<string> Player::resourcesAndKnightIHave()
    {
        vector<string> resurceIhave;
        vector<string> allResurces = {"Brick", "Wood", "Sheep", "Grain", "Ore"};
        for (int i = 0; i < allResurces.size(); i++)
        {
            if (iHave(allResurces[i].substr(0, 1)))
            {
                resurceIhave.push_back(allResurces[i]);
            }
        }
        if(iHave("knight")){
            resurceIhave.push_back("knight");
        }
        return resurceIhave;
    }

    vector<string> Player::iCanBuild()
    {
        vector<string> myOption;
        if (this->iHave("W") && this->iHave("B"))
        {
            myOption.push_back("Road");
        }

        if (this->iHave("W") && this->iHave("B") && this->iHave("G") && this->iHave("S"))
        {
            myOption.push_back("Village");
        }

        if (this->iHave("G", 2) && this->iHave("O", 3))
        {
            myOption.push_back("City");
        }
        if (this->iHave("G") && this->iHave("S") && this->iHave("O"))
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

    void Player::printMyCard()
    {
        cout << "Player " << this->name << " have: " << endl;
        cout << endl;
        cout << "Brick: " << this->playerCard["B"] << endl;
        cout << "Wood: " << this->playerCard["W"] << endl;
        cout << "Sheep: " << this->playerCard["S"] << endl;
        cout << "Grain: " << this->playerCard["G"] << endl;
        cout << "Ore: " << this->playerCard["O"] << endl;
        cout << endl;
        cout << "knight: " << this->playerCard["knight"] << endl;
        cout << "victory point: " << this->playerCard["victory point"] << endl;
        cout << "build 2 road: " << this->playerCard["build 2 road"] << endl;
        cout << "year of plenty: " << this->playerCard["year of plenty"] << endl;
        cout << "monopoly: " << this->playerCard["monopoly"] << endl
             << endl;
    }

    int Player::cheackScore()
    {
        score = private_score + public_score;
        return score;
    }

    vector<string> Player::getMyDVLPCard()
    {
        int i = 0;
        vector<string> devCards{
            4,
        };
        if (playerCard["knight"] > 0)
        {
            devCards[i] = "knight";
            i++;
        }

        if (playerCard["build 2 road"] > 0)
        {
            devCards[i] = "build 2 road";
            i++;
        }
        if (playerCard["year of plenty"] > 0)
        {
            devCards[i] = "year of plenty";
            i++;
        }
        if (playerCard["monopoly"] > 0)
        {
            devCards[i] = "monopoly";
            i++;
        }
        devCards.resize(i);
        return devCards;
    }

    int Player::getAmountOfResource(string resource)
    {
        return playerCard[resource];
    }

    void Player::printMyResources()
    {
        vector<string> resources({"Brick", "Wood", "Sheep", "Grain", "Ore"});
        int i = 0;
        for (string resource : resources)
        {
            cout << "(" << i << ") " << resource << ": " << playerCard[resource.erase(1)] << endl;
            i++;
        }
    }
    
    int Player::getResourcesDeckSize()
    {
        return numOfResource;
    }
};
