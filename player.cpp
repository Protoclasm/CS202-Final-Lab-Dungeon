#include "player.h"
#include "rooms.h"
#include <iostream>
#include <cctype>

//Following two functions are helpers.
std::string getDirectionName(const char direction) {
    switch(direction) {
        case 'n':
            return "north";
        case 's': 
            return "south";
        case 'e':
            return "east";
        case 'w':
            return "west";
    }
    return "ERROR";
}

int getExit(const Rooms &room, const char direction) {
    switch(direction)
    {
        case 'n':
            return room.north;
        case 's':
            return room.south;
        case 'e':
            return room.east;
        case 'w':
            return room.west;
    }
    return 0; //Returns 0 to avoid warnings.
}

Player::Player() {
    char confirmation = ' ';
    while(toupper(confirmation) != 'Y') {
        std::cout << "Please enter your character's name: ";
        getline(std::cin, this->name, '\n');
        std::cout << "Are you sure you want " << this->name << " to be your name (y or n)? ";
        std::cin >> confirmation;
    }
    atk = 5; //Starting atk = 5;
    maxHP = currentHP = 10; //Starting HP = 10
}

const int Player::getAttack() {
    return atk;
}

const int Player::getCurrentHP() {
    return currentHP;
}

const int Player::getMaxHP() {
    return maxHP;
}

const std::string Player::getPlayerName() {
    return name;
}

void Player::look(const Rooms &room) {
    std::cout << '\n' << room.name << '\n' << room.description << '\n' << "\nExits:";
    if(-1 < room.north) std::cout << " n";
    if(-1 < room.south) std::cout << " s";
    if(-1 < room.east) std::cout << " e";
    if(-1 < room.west) std::cout << " w";
    std::cout << std::endl;
}

void Player::move(const Rooms *room, size_t &currentRoom) {
    char exitChoice;
    while(true) {
        std::cout << "Which exit would you like to take?" << std::endl;
        std::cin >> exitChoice;
        switch(exitChoice) {
            case 'n': case 's' : case 'e' : case 'w':
                if(-1 == getExit(room[currentRoom], exitChoice)) {
                    std::cout << "You can't go " << getDirectionName(exitChoice) << '!' << std::endl;
                    break;
                }
                //Following code is for a valid direction input.
                std::cout << "You moved " << getDirectionName(exitChoice) << '.' << std::endl;
                currentRoom = getExit(room[currentRoom], exitChoice); 
                return;
            default:
                std::cout << "Invalid exit!" << std::endl;
                break;
        }
    }
}

const void Player::decisions(Bag &inventory, const Rooms *room, size_t &currentRoom) {
    char choice = ' ';
    while(choice != 'Q') {
        std::cout << "\n\033[4mAvailable Options\033[0m\nM) Move\nL) Look\nB) Bag\nR) Room Art\nE) Enemy Art\nS) Stats\nQ) Quit\nPlease enter your letter choice: ";
        while(true) {
            std::cin >> choice;
            choice = std::toupper(choice);
            if(choice == 'M' || choice == 'L' || choice == 'B' || choice == 'S' || choice == 'R' || choice == 'E' || choice == 'Q') break;
            std::cout << "Invalid choice. Please enter M, L, B, S, R, E, or Q: ";
        }
        switch(choice) {
            case 'M': //For movement. TODO: NEED TO MAKE IT TO WHERE THE ROOM OBJECT DOES CHANGE.
                move(room, currentRoom);
                break;
            case 'L': //For look.
                look(room[currentRoom]);
                break;
            case 'B': //Bag.
                inventory.interactBag(this);
                break;
            case 'S': //Stats.
                std::cout << "\n\033[4m" << name << "'s stats\033[0m" << std::endl; //Underlined playerName's stats.
                std::cout << "HP: " << currentHP << '/' << maxHP << std::endl;
                std::cout << "ATK: " << atk << std::endl;
                break;
            case 'R': //Print room art.
                std::cout << room[currentRoom].ASCIIRoomsArt << std::endl; //Will this need an endl?
                break;
            case 'E': //Print enemy art.
                if(room[currentRoom].enemy != NULL) std::cout << room[currentRoom].ASCIIEnemyArt << std::endl;
                else std::cout << "There is no enemy in this room!" << std::endl;
            case 'Q': //Quit game.
                std::cout << "Thank you for playing, " << name << '!' << std::endl;
                return;
        }
    }
        return;
}