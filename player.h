#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <string>
#include "bag.h"

class Bag;
class Rooms;

class Player {
    friend class Bag;
    public:
        Player(); //Prompts for user name (asks for confirmation) and sets base atk & hp to 5 and 10 respectively.
        const int getAttack();
        const int getCurrentHP();
        const int getMaxHP();
        const std::string getPlayerName();
        const void decisions(Bag &inventory, const Rooms *room);
        void displayStats();
        bool combat(const Rooms &room, Bag &inventory);
    private:
        int maxHP;
        int currentHP;
        int atk;
        std::string name;
};

#endif