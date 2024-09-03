
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream> // For std::cout, std::endl
#include "player.hpp" // Include necessary headers

// ANSI color codes for console output
#define BLUE "\033[34m"    /* Blue */
#define GREEN "\033[32m"   /* Green */
#define PURPLE "\033[35m"  /* Purple */

using namespace std;

namespace ariel
{
    class Player
    {
    private:
        // Private member variables
        string name;            // Player's name
        string collor;          // Player's color
        int score;              // Total score (private + public)
        int private_score;      // Private score
        int numOfResource;      // Number of resources owned
        map<string, int> playerCard; // Map of resources and development cards owned

    public:
        // Constructors
        Player(string name);    // Parameterized constructor
        Player();               // Default constructor

        // Getters and setters
        void setName(string newName);       // Sets player's name
        string getName() const;             // Gets player's name
        void setCollor(string newCollor);   // Sets player's color
        string getCollor() const;           // Gets player's color
        int public_score;       // Public score
        int usedKnight;         // Number of knights used
        int used_road;          // Number of roads built
        int used_village;       // Number of villages built
        int used_city;          // Number of cities built

        // Resource management methods
        void addResurces(string resourceToAdd);        // Adds a resource
        void addResurces(string resourceToAdd, int amount); // Adds multiple resources
        void removeResurces(string resourceToRemove);  // Removes a resource
        void removeResurces(string resourceToRemove, int amount); // Removes multiple resources
        int getAmountOfResource(string resource);     // Gets the amount of a specific resource
        int getResourcesDeckSize();                   // Gets the total number of resources

        // Building methods
        void build();                               // Displays build options
        void build(string whatToBuild);             // Executes specific build action
        bool iCanBuild(string building);            // Checks if player can build a specific item
        vector<string> iCanBuild();                 // Returns a vector of build options
        void addRoad();                             // Adds a road
        void addVillage();                          // Adds a village
        void addCity();                             // Adds a city

        // Development card methods
        vector<string> getMyDVLPCard();             // Returns a vector of development cards owned
        void addPrivateScore();                     // Increases private score
        int cheackScore();                          // Calculates and returns total score
        vector<string> resourcesAndKnightIHave();   // Returns resources and knights owned
        bool iHave(string cardName);                // Checks if player has a specific card
        bool iHave(string cardName, int amount);    // Checks if player has a specific number of cards

        // Printing methods
        void printMyCard();                         // Prints player's resource and development card status
        void printMyResources();                    // Prints player's current resource quantities
    };
}

#endif // PLAYER_HPP
