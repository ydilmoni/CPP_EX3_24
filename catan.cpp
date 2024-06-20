#include "catan.hpp"
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#define RESET "\033[0m"
#define BLUE "\033[34m"   /* Blue */
#define GREEN "\033[32m"  /* Green */
#define PURPLE "\033[35m" /* Purple */

namespace ariel
{

    Catan::Catan(Player &p1, Player &p2, Player &p3)
    {
        map<string, Deck> decs = {
            {"W", Deck("W")},
            {"B", Deck("B")},
            {"S", Deck("S")},
            {"O", Deck("O")},
            {"G", Deck("G")},
            {"dvl", Deck()}};
        this->decks = decs;

        // decks["dvl"].printDeck();
        // decks["W"].printDeck();
        // decks["B"].printDeck();
        // decks["S"].printDeck();

        this->players.push_back(ref(p1));
        p1.setCollor(BLUE);
        this->players.push_back(ref(p2));
        p2.setCollor(GREEN);
        this->players.push_back(ref(p3));
        p3.setCollor(PURPLE);
        cout << string(RESET) << endl;
        gameNode.resize(54, make_pair(nullptr, ""));
        initializingGameEdges();
        initializingGameNode();

        this->printBoard2();
        for (int i = 0; i < players.size(); i++)
        {
            cout << players[i].get().getCollor() << players[i].get().getName() << " collor" << RESET << endl;
        }

        this->startGame();
        this->restOfGame();
    }

    Catan::Catan()
    {
        Player p1("Player 1");
        Player p2("Player 2");
        Player p3("Player 3");

        Catan(p1, p2, p3);
    }

    void Catan::startGame()
    {

        random_device rd;
        mt19937 g(rd());
        shuffle(players.begin(), players.end(), g);
        cout << "Starting the game, the first player is " << players[0].get().getCollor() << players[0].get().getName() << RESET << endl;
        cout << endl;
        // this_thread::sleep_for(chrono::seconds(5));

        first2village();
    }

    void Catan::first2village()
    {
        cout << "Let's start by placing 2 villages" << endl;
        int i;
        for (i = 0; i < players.size(); i++)
        {
            putVillageAndRoad(i);
        }
        for (int j = 2; j >= 0; j--)
        {
            putVillageAndRoad(j);
        }
    }

    void Catan::putVillageAndRoad(int playerIndex)
    {
        cout << players[playerIndex].get().getCollor() << players[playerIndex].get().getName() << "'s turn" << RESET << endl;
        int place;
        // vector<int> villageOption = getUnoccupiedNodeVector();
        // cout << "Where would you like to build your village?" << endl;
        // printVector(villageOption);
        cout << endl
             << endl;
        cout << "Choose location for your village" << endl;
        cin >> place;

        while (place < 0 || place > 53 || gameNode[place].first != NULL || !canBuildThere(place))
        {
            cout << "You have chosen a place that is already occupied or does not exist because it is not in the range 0-53,\
                 please choose another place"
                 << endl;
            cin >> place;
        }

        setGameNode(place, players[playerIndex], "Village");
        players[playerIndex].get().addVillage();
        cout << players[playerIndex].get().getCollor() << players[playerIndex].get().getName() << " put a Village in node " << place << RESET << endl;

        buildFreeRoad(playerIndex, place);
        // this->printAllGameEdges();

        printBoard2();
        cout << endl;
    }

    void Catan::buildFreeRoad(int playerIndex, int place)
    {
        cout << "Choose a place to put a road: " << endl;
        vector<pair<int, int>> roadOption;
        if (place == -1)
        {
            roadOption = getPlacesForRoadByPlayerIndex(playerIndex);
        }
        else
        {
            roadOption = getUnoccupiedConnectedEdges(place);
        }

        printVector(roadOption);
        int option;
        cin >> option;
        while (option < 0 || option > roadOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        this->setGameEdges(roadOption[option].first, roadOption[option].second, players[playerIndex]);

        players[playerIndex].get().build("freeRoad");

        cout << players[playerIndex].get().getCollor() << players[playerIndex].get().getName() << "put a road in " << roadOption[option].first << " , " << roadOption[option].second << RESET << endl;
    }

    void Catan::restOfGame()
    {
        int i = 0;
        bool someoneWin = false;
        while (!someoneWin)
        {
            i = i % 3;
            bool continueMyturn = true;

            int dice = (rand() % 6 + 1) + (rand() % 6 + 1);
            dealResurces(dice);
            while (continueMyturn)
            {
                cout << RESET << endl;
                printBoard2();
                cout << "You rolled a " << dice << endl;
                // cout << "Player " << players[i].get().getCollor() << players[i].get().getName() << "'s turn" << RESET << endl;
                cout << players[i].get().getCollor() << "Player " << players[i].get().getName() << "'s turn" << endl;

                players[i].get().printMyCard();
                int option;

                cout << "What would you like to do?" << endl;
                cout << "0.   End Turn" << endl;
                cout << "1.   Trade" << endl;
                cout << "2.   Build" << endl;
                cout << "3.   Use a Development Card" << endl;
                cout << "4.   I win" << endl;
                cin >> option;
                while (option < 0 || option > 4)
                {
                    cout << "Invalid option, please choose again" << endl;
                    cin >> option;
                }
                if (option == 0)
                {
                    cout << "End Turn." << endl;
                    continueMyturn = false;
                }
                else if (option == 1)
                {
                    cout << "Trade:" << endl;
                    trade(i);
                }
                else if (option == 2)
                {
                    cout << "Build:" << endl;
                    iCanBuild(i);
                }

                else if (option == 3)
                {
                    cout << "Use a Development Card:" << endl;
                    chooseDevelopmentCard(i);
                }

                else if (option == 4)
                {
                    cout << "I win" << endl;
                    continueMyturn = false;
                    someoneWin = true;
                }
                else{

                }
            }
            i++;
        }
        cout << "END THE GAME!!" << endl;
    }

    void Catan::iCanBuild(int playerIndex)
    {
        vector<string> buildOption = {"Raod", "Village", "City", "Buy Development Card", "Nothing, go back"};

        cout << "what to build: " << endl;
        int i;
        for (i = 0; i < buildOption.size(); i++)
        {
            cout << "(" << to_string(i) << ") " << buildOption[i] << endl;
        }

        int whatToBuild;

        cout << "What do you want to build? (choose a number) " << endl;
        cin >> whatToBuild;
        while (whatToBuild < 0 || whatToBuild > 4)
        {
            cout << "choose a number" << endl;
            cin >> whatToBuild;
        }
        if (whatToBuild == 0)
        {
            if (players[playerIndex].get().iCanBuild("Road"))
            {
                putRoad(playerIndex);
            }
            else
            {
                cout << "You don't have the resources to build a road" << endl;
            }
        }
        else if (whatToBuild == 1)
        {
            if (players[playerIndex].get().iCanBuild("Village"))
            {
                putVillage(playerIndex);
            }
            else
            {
                cout << "You don't have the resources to build a village" << endl;
            }
        }
        else if (whatToBuild == 2)
        {
            if (players[playerIndex].get().iCanBuild("City"))
            {
                putCity(playerIndex);
            }
            else
            {
                cout << "You don't have the resources to build a city" << endl;
            }
        }
        else if (whatToBuild == 3)
        {
            if (players[playerIndex].get().iCanBuild("Buy Development Card"))
            {
                buyDevelopmentCard(playerIndex);
            }
            else
            {
                cout << "You don't have the resources to buy a development card" << endl;
            }
        }
        //     buyDvlpCard(playerIndex);
        // }
    }

    void Catan::putVillage(int playerIndex)
    {
        int place;
        cout << "Where would you like to build your village?" << endl;
        vector<int> villageOption = getPlaceForVillageByPlayerIndex(playerIndex);
        villageOption.push_back(-1);
        for (int i = 0; i < villageOption.size(); i++)
        {
            cout << "(" << to_string(i) << ")" << to_string(villageOption[i]) << endl;
        }

        cin >> place;
        while (place < -1 || place >= villageOption.size())
        {
            cout << "Invalid choice. Please choose again." << endl;
            cin >> place;
        }
        if (villageOption[place] != -1)
        {
            gameNode[villageOption[place]] = make_pair(&players[playerIndex].get(), "Village");
            players[playerIndex].get().build("Village");
            returnCardToDeck("W");
            returnCardToDeck("B");
            returnCardToDeck("S");
            returnCardToDeck("G");
            cout << "Village placed successfully!" << endl;
        }
    }

    void Catan::putRoad(int playerIndex)
    {
        cout << "Choose a place to put a road: " << endl;
        vector<pair<int, int>> roadOption = getPlacesForRoadByPlayerIndex(playerIndex);
        printVector(roadOption);
        int option;
        cin >> option;
        while (option < 0 || option > roadOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        players[playerIndex].get().build("Road");
        setGameEdges(roadOption[option].first, roadOption[option].second, players[playerIndex]);

        cout << "Road placed successfully!" << endl;
        returnCardToDeck("W");
        returnCardToDeck("B");
    }

    void Catan::putCity(int playerIndex)
    {
        int place;
        cout << "Where would you like to build your city?" << endl;
        vector<int> cityOption = getPlaceForCityByPlayerIndex(playerIndex);
        for (int i = 0; i < cityOption.size(); i++)
        {
            cout << "(" << to_string(i) << ")" << to_string(cityOption[i]) << endl;
        }
        cin >> place;
        while (place < 0 || place > cityOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> place;
        }
        gameNode[cityOption[place]] = make_pair(&players[playerIndex].get(), "City");
        players[playerIndex].get().build("City");
        cout << "City placed successfully!" << endl;
        returnCardToDeck("G", 2);
        returnCardToDeck("O", 3);
    }

    void Catan::trade(int playerIndex)
    {
        vector<string> resources = {"Brick", "Wood", "Sheep", "Grain", "Ore"};
        cout << "What would you like to trade?" << endl;
        printVector(resources);
        int option;
        cin >> option;
        while (option < 0 || option > resources.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        string resource = resources[option].erase(1);

        if (players[playerIndex].get().iHave(resource, 4))
        {

            cout << "What would you like to trade for?" << endl;
            printVector(resources);
            int tradeOption;
            cin >> tradeOption;
            while (tradeOption < 0 || tradeOption > resources.size() - 1)
            {
                cout << "Invalid option, please choose again" << endl;
                cin >> tradeOption;
            }
            string tradeResource = resources[tradeOption].erase(1);
            if (decks[tradeResource].size > 0)
            {
                players[playerIndex].get().removeResurces(resource, 4);
                players[playerIndex].get().addResurces(tradeResource);
                decks[resources[tradeOption].erase(1)].drawCard();
                returnCardToDeck(resource, 4);
            }
        }
    }

    void Catan::buyDevelopmentCard(int playerIndex)
    {
        string card = decks["dvl"].drawCard();
        if (card != "")
        {
            players[playerIndex].get().build("Buy Development Card");
            players[playerIndex].get().addResurces(card);
            //TODO: לא מחזיר משאבים לקופה
        }
    }

    void Catan::chooseDevelopmentCard(int playerIndex)
    {
        cout << endl;
        vector<string> myDevlopCard = players[playerIndex].get().getMyDVLPCard();

        if (myDevlopCard.size() < 1)
        {
            return;
        }

        printVector(myDevlopCard);
        int option;
        cin >> option;
        while (option < 0 || option > myDevlopCard.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        if (myDevlopCard[option] == "victory point")
        {
            cout << "Can't use victory point" << endl;
        }

        else
        {
            useDevelopmentCard(myDevlopCard[option], playerIndex);
        }
    }

    void Catan::useDevelopmentCard(string card, int playerIndex)
    {
        if (card == "knight")
        {
            players[playerIndex].get().usedKnight++;
        }

        else if (card == "monopoly")
        {
            useMonopoly(playerIndex);
        }
        else if (card == "build 2 road")
        {
            useRoadBuilding(playerIndex);
        }
        else if (card == "year of plenty")
        {
            useYearOfPlenty(playerIndex);
        }
        else if (card == "victory point")
        {
            return;
        }
        players[playerIndex].get().removeResurces(card);
    }

    void Catan::useRoadBuilding(int playerIndex)
    {
        buildFreeRoad(playerIndex, -1);
        buildFreeRoad(playerIndex, -1);
    }

    void Catan::useMonopoly(int playerIndex)
    {
        vector<string> myOption({"Wood", "Brick", "Sheep", "Grain", "Ore"});
        printVector(myOption);
        int option;
        cin >> option;
        while (option < 0 || option > myOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        string resource = myOption[option];
        cout << "I want to take " << resource << " from everyone" << endl;

        for (int i = 0; i < players.size(); i++)
        {
            if (i != playerIndex)
            {
                int amount = players[i].get().getAmountOfResource(resource.erase(1));
                if (amount > 0)
                {
                    players[playerIndex].get().addResurces(resource.erase(1), amount);
                    players[i].get().removeResurces(resource.erase(1), amount);
                }
            }
        }
    }

    void Catan::useYearOfPlenty(int playerIndex)
    {
        vector<string> myOption({"Wood", "Brick", "Sheep", "Grain", "Ore"});
        printVector(myOption);
        int option;
        cout << "first resource to take" << endl;
        cin >> option;
        while (option < 0 || option > myOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        string resource1 = myOption[option];
        cout << "secund resource to take" << endl;
        cin >> option;
        while (option < 0 || option > myOption.size() - 1)
        {
            cout << "Invalid option, please choose again" << endl;
            cin >> option;
        }
        string resource = myOption[option];
        cout << "I want to take " << resource1 << " and " << resource << endl;
        players[playerIndex].get().addResurces(resource1.erase(1));
        players[playerIndex].get().addResurces(resource.erase(1));
    }

    void Catan::returnCardToDeck(string card, int amount)
    {
        decks[card].addToDeck(card,amount);
    }

    void Catan::returnCardToDeck(string card)
    {
        returnCardToDeck(card, 1);
    }

    void Catan::initializingGameNode()
    {
        for (int i = 0; i < 54; i++)
        {
            gameNode[i] = (make_pair(nullptr, ""));
        }
    }

    void Catan::setGameNode(int nodeIndex, Player &player, string buildingType)
    {
        gameNode[nodeIndex] = make_pair(&player, buildingType);
    }

    void Catan::printAllNodeInformation() const
    {
        for (int i = 0; i < 54; i++)
        {
            if (gameNode[i].first != nullptr)
            {
                cout << "Node " << i << " is occupied by " << gameNode[i].first->getName() << " with a " << gameNode[i].second << endl;
            }
            else
            {
                cout << "Node " << i << " is not occupied" << endl;
            }
        }
    }

    vector<int> Catan::getUnoccupiedNodeVector()
    {
        vector<int> unoccupiedNode;
        for (int i = 0; i < 54; i++)
        {
            if (canBuildThere(i))
            {
                unoccupiedNode.push_back(i);
            }
        }
        return unoccupiedNode;
    }

    bool Catan::canBuildThere(int nodeIndex)
    {
        bool result = false;
        if (gameNode[nodeIndex].first != nullptr)
        {
            return false;
        }
        for (const auto &[key, values] : Board::node_to_adjacentNode)
        {
            if (key == nodeIndex)
            {
                for (int i = 0; i < values.size(); i++)
                {
                    if (gameNode[values[i]].first != nullptr)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void Catan::setGameEdges(int start, int end, Player &player)
    {
        this->gameEdges[{start, end}] = &player;
        this->gameEdges[{end, start}] = &player;
    }

    vector<pair<int, int>> Catan::getUnoccupiedConnectedEdges(int node) const
    {
        vector<pair<int, int>> unoccupiedEdges;
        for (const auto &[edge, player] : gameEdges)
        {
            if (player == nullptr && (edge.first == node || edge.second == node))
            {
                unoccupiedEdges.push_back(edge);
            }
        }
        return unoccupiedEdges;
    }

    void Catan::initializingGameEdges()
    {
        for (const auto &[key, values] : Board::node_to_adjacentNode)
        {
            for (int value : values)
            {
                if (key < value)
                {
                    gameEdges[{key, value}] = nullptr;
                }
            }
        }
    }

    void Catan::printAllGameEdges() const
    {
        for (const auto &[edge, player] : gameEdges)
        {
            if (edge.first < edge.second)
            {
                cout << "(" << edge.first << ", " << edge.second << ")";
                if (player)
                {
                    cout << " - Controlled by: " << player->getCollor() << player->getName() << RESET;
                }
                cout << endl;
            }
        }
    }

    void Catan::printUnoccupiedEdge() const
    {
        for (const auto &[edge, player] : gameEdges)
        {
            if (!player)
            {
                cout << "(" << edge.first << ", " << edge.second << ")";
            }
        }
    }

    vector<pair<int, int>> Catan::getPlacesForRoadByPlayerIndex(int playerIndex)
    {
        vector<pair<int, int>> placesForRoad;
        for (const auto &[edge, player] : gameEdges)
        {
            if (player && player == &players[playerIndex].get())
            {
                vector<pair<int, int>> unoccupiedConnectedEdges = getUnoccupiedConnectedEdges(edge.first);
                for (const auto &unoccupiedEdge : unoccupiedConnectedEdges)
                {
                    placesForRoad.push_back(unoccupiedEdge);
                }
            }
        }
        return placesForRoad;
    }

    vector<int> Catan::getPlaceForCityByPlayerIndex(int playerIndex)
    {
        vector<int> placesForCity;
        for (int i = 0; i < gameNode.size(); i++)
        {
            if (gameNode[i].first == &players[playerIndex].get() && gameNode[i].second == "Village")
            {
                placesForCity.push_back(i);
            }
        }
        return placesForCity;
    }

    vector<int> Catan::getPlaceForVillageByPlayerIndex(int playerIndex)
    {
        vector<int> placesForVillage;
        for (int i = 0; i < gameNode.size(); i++)
        {
            if (gameNode[i].first == nullptr)
            {
                vector<int> adjacentNode = Board::node_to_adjacentNode[i];
                bool canBuild = true;
                for (int node : adjacentNode)
                {
                    if (gameNode[node].first != nullptr)
                    {
                        canBuild = false;
                    }
                }
                if (canBuild)
                {
                    for (const auto &[edge, player] : gameEdges)
                    {
                        if ((edge.first == i || edge.second == i) && player == &players[playerIndex].get())
                        {
                            placesForVillage.push_back(i);
                        }
                    }
                }
            }
        }
        return placesForVillage;
    }

    void Catan::dealResurces(int number)
    {
        for (Tile t : this->board.tiles)
        {
            if (t.number == number)
            {
                for (const auto &[key, values] : Board::tileLocation_to_adjacentNode)
                {
                    if (t.tile_location == key)
                    {
                        for (int node : values)
                        {
                            if (gameNode[node].first != nullptr)
                            {
                                string card = this->decks[t.landType].drawCard();
                                if (card != "")
                                {
                                    gameNode[node].first->addResurces(t.landType);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    string Catan::p(int tileNum)
    {
        string result = string(this->board.tiles[tileNum].collor) + this->board.tiles[tileNum].getType() + string(this->board.tiles[tileNum].collor) + to_string(this->board.tiles[tileNum].getNum()) + string(RESET);
        return result;
    }

    string Catan::pr(int start, int end, string whatToPrint)
    {
        string result = "";
        string collor = RESET;
        for (const auto &[edge, player] : gameEdges)
        {
            if (edge.first == start && edge.second == end && player != nullptr)
            {
                collor = player->getCollor();
            }
        }
        result = string(collor) + whatToPrint + string(RESET);
        return result;
    }

    string Catan::pr(int start, int end)
    {
        return p2(start) + string(RESET) + "-" + pr(start, end, "(R)") + string(RESET) + "-" + p2(end);
    }

    string Catan::p2(int nodeNum)
    {
        for (int i = 0; i < this->gameNode.size(); i++)
        {
            if (i == nodeNum)
            {
                if (gameNode[i].first != nullptr)
                {
                    if (gameNode[i].second == "Village")
                    {
                        return string(gameNode[i].first->getCollor()) + "[" + to_string(i) + "]" + string(RESET);
                    }
                    else if (gameNode[i].second == "City")
                    {
                        return string(gameNode[i].first->getCollor()) + "{" + to_string(i) + "}" + string(RESET);
                    }
                }
                else
                {
                    return string(RESET) + "[" + to_string(i) + "]" + string(RESET);
                }
            }
        }
        cout << "cant find this num" << endl;
        return "";
    }

    string Catan::d1(int start, int end)
    {
        return pr(start, end, "/");
    }

    string Catan::d2(int start, int end)
    {
        return pr(start, end, "\\");
    }

    string Catan::m(int start, int end)
    {
        return pr(start, end, "(R)");
    }

    string Catan::ms(int amount, int firstStart, int firstEnd)
    {
        int times = 9;
        string space = " ";
        string s;
        for (int i = 0; i < amount; i++)
        {
            s += m(firstStart, firstEnd) + times * space;
            firstStart++;
            firstEnd++;
        }
        return s;
    }

    void Catan::printBoard2()
    {
        string output = "";
        output += "     \n";
        output += "                               " + pr(0, 1) + "    \n";
        output += "                               /         \\  \n";
        output += "                             " + ms(2, 0, 3) + "   \n";
        output += "                             /             \\                              \n";
        output += "                    " + pr(2, 3) + "     " + p(0) + "      " + pr(4, 5) + "   \n";
        output += "                   /         \\             /         \\  \n";
        output += "                 " + ms(4, 2, 7) + "    \n";
        // output += "                 " + m(2,7) + "          " + m(3,8) + "         " +  m(4,9) + "          " +  m(5,10) + "    \n";
        output += "                 /             \\         /             \\  \n";
        output += "      " + pr(6, 7) + "      " + p(1) + "    " + pr(8, 9) + "      " + p(2) + "     " + pr(10, 11) + "                              \n";
        output += "      /         \\             /         \\             /         \\            \n";
        output += "    " + ms(6, 6, 12) + " \n";
        // output += "    (0)          (0)         (0)          (0)         (0)          (0)                             \n";
        output += "    /             \\         /             \\         /             \\                            \n";
        output += "  " + p2(12) + "     " + p(3) + "    " + pr(13, 14) + "     " + p(4) + "   " + pr(15, 16) + "     " + p(5) + "     " + p2(17) + "                                   \n";
        output += "    \\             /         \\             /         \\             /                  \n";
        output += "    " + ms(6, 12, 18) + "       \n";
        // output += "    (0)         (0)          (0)         (0)          (0)          (0)                              \n";
        output += "      \\         /             \\         /             \\         /                \n";
        output += "     " + pr(18, 19) + "     " + p(6) + "    " + pr(20, 21) + "     " + p(7) + "   " + pr(22, 23) + "                                   \n";
        output += "      /         \\             /         \\             /         \\                  \n";
        output += "    " + ms(6, 18, 24) + "      \n";
        // output += "    (0)          (0)         (0)          (0)         (0)          (0)                              \n";
        output += "    /             \\         /             \\         /             \\            \n";
        output += "  " + p2(24) + "    " + p(8) + "     " + pr(25, 26) + "     " + p(9) + "     " + pr(27, 28) + "     " + p(10) + "   " + p2(29) + "                                   \n";
        output += "    \\             /         \\             /         \\             /                   \n";
        output += "    " + ms(6, 24, 30) + "                              \n";
        // output += "    (0)         (0)          (0)         (0)          (0)          (0)                              \n";
        output += "      \\         /             \\         /             \\         /                 \n";
        output += "     " + pr(30, 31) + "    " + p(11) + "     " + pr(32, 33) + "     " + p(12) + "     " + pr(34, 35) + "                                    \n";
        output += "      /         \\             /         \\             /         \\                    \n";
        output += "    " + ms(6, 30, 36) + "                              \n";
        // output += "    (0)          (0)         (0)          (0)         (0)          (0)                              \n";
        output += "    /             \\         /             \\         /             \\                            \n";
        output += "  " + p2(36) + "     " + p(13) + "     " + pr(37, 38) + "     " + p(14) + "   " + pr(39, 40) + "     " + p(15) + "   " + p2(41) + "                              \n";
        output += "    \\             /         \\             /         \\             /          \n";
        output += "    " + ms(6, 36, 42) + "       \n";
        // output += "    (0)         (0)          (0)         (0)          (0)          (0)                             \n";
        output += "      \\         /             \\         /             \\         /             \n";
        output += "     " + pr(42, 43) + "    " + p(16) + "     " + pr(44, 45) + "    " + p(17) + "     " + pr(46, 47) + "                                    \n";
        output += "                \\             /         \\             /                                                 \n";
        output += "                " + ms(4, 43, 48) + "                           \n";
        // output += "                 (0)         (0)          (0)         (0)                           \n";
        output += "                  \\         /             \\         /                                 \n";
        output += "                 " + pr(48, 49) + "     " + p(18) + "   " + pr(50, 51) + "                                         \n";
        output += "                            \\             /                                            \n";
        output += "                            " + ms(2, 49, 52) + "                                  \n";
        // output += "                              (0)         (0)                                  \n";
        output += "                              \\         /                                   \n";
        output += "                             " + pr(52, 53) + "                                         \n";

        cout << "print the board" << endl;
        cout << output << endl;
    }

    void Catan::printOptionFromVector(vector<int> &vec) const
    {
        for (int i = 0; i < vec.size(); i++)
        {
            cout << "(option " << i << ") " << vec[i] << endl;
        }
    }

    void Catan::printVector(vector<string> &vec) const
    {
        for (int i = 0; i < vec.size(); i++)
        {
            cout << "(" << i << ") " << vec[i] << endl;
        }
    }

    ostream &operator<<(ostream &os, pair<int, int> edge)
    {
        os << edge.first << ", " << edge.second << endl;
        return os;
    }

    ostream &operator<<(ostream &os, const pair<ariel::Player *, string> &p)
    {
        os << "(Player: " << p.first << ", String: " << p.second << ")";
        return os;
    }

    string operator*(const string &s, int n)
    {
        std::string result;
        for (int i = 0; i < n; ++i)
        {
            result += s;
        }
        return result;
    }

    string operator*(int n, const string &s)
    {
        return s * n; // Reuse the above function
    }
}
