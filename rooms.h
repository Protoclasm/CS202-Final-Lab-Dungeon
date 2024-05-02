#ifndef ROOMS_H
#define ROOMS_H

#include <string>
#include <vector>

#include "enemies.h"

class Enemies; //Forward declaration for compiling.

class Rooms {
    friend class Bag;
    friend class Player;
    public:
        //Following four variables will hold which rooms the direction leads to.
        Rooms();
        ~Rooms();
        int north;
        int south;
        int east;
        int west; 
        std::string name;
        std::string description;
        std::string ASCIIRoomArt;
        const std::string getASCIIRoomArt();
    private:
        void createEnemy(std::string enemyName, std::string enemyDialogue, std::string ASCIIEnemyArt, int HP, int atk); //Ran if there is an enemy inside file for the rooms.
        void deleteEnemy(); //Ran when enemy's health == 0.
        Enemies *enemy; //Will either point to NULL or a created enemy.
};

#endif