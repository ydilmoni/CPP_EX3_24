#include "player.hpp"
#include <iostream>
namespace ariel
{
    Player::Player(string playerName)
        : name(playerName), score(0), private_score(0), used_road(0), used_village(0),
          used_city(0), public_score(0)
    {

        playerCard["W"] = 0;
        playerCard["B"] = 0;
        playerCard["G"] = 0;
        playerCard["S"] = 0;
        playerCard["O"] = 0;
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
    string Player::getCollor() const
    {
        return this->collor;
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
    }

    void Player::removeResurces(string resourceToRemove)
    {
        this->removeResurces(resourceToRemove, 1);
    }

    void Player::removeResurces(string resourceToRemove, int amount)
    {
        playerCard[resourceToRemove] -= amount;
    }

    void Player::trade()
    {
        vector<string> resurceIhave=iHave();
        vector <string> allResurces = {"W", "O", "G", "S", "B"};
        int wantToTrade;
        cout << "What do you want to give?"<<endl;
        for (size_t i = 0; i < resurceIhave.size() ; i++)  
        {
            cout<<"("<<i<<") "<<resurceIhave[i]<<endl;
        }

        cin>>wantToTrade;
        while(wantToTrade<0 || wantToTrade>resurceIhave.size()){
            cout<<"Invalid input, please try again."<<endl;
            cin>>wantToTrade;
        }
        cout << "What do you want to get?"<<endl;     
        for (size_t i = 0; i < allResurces.size() ; i++){
            cout<<"("<<i<<") "<<allResurces[i]<<endl;
        }
        int wantToGet;
        cin>>wantToGet;
        while(wantToGet<0 || wantToGet>allResurces.size()){
            cout<<"Invalid input, please try again."<<endl; 
            cin>>wantToGet;
        }
        cout << "Did someone want to trade?"<<endl;
        cout<<"0 - no"<<endl;
        cout<<"1 - yes"<<endl;
        int trade;
        cin>>trade;
        if(trade==1){
            
        }


        
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
        if (whatToBuild > 0 && whatToBuild < myOption.size()-1)
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
            this->removeResurces("O", 3);
            this->removeResurces("G", 2);
            this->addCity();
        }
        else if (whatToBuild == "Buy Development Card")
        {
            this->removeResurces("O");
            this->removeResurces("G");
            this->removeResurces("S");
            this->buyDevelopmentCard();
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

    vector<string> Player::iHave()
    {
        vector<string> resurceIhave;
        vector <string> allResurces = {"W", "O", "G", "S", "B"};
        for (int i = 0; i < allResurces.size(); i++)
        {
            if (iHave(allResurces[i])){
                resurceIhave.push_back(allResurces[i]);
            }
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
    void Player::buyDevelopmentCard()
    {
    }
    void Player::useDevelopmentCard()
    {
    }
};
