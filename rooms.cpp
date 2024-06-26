#include <iostream>
#include <fstream>
#include <sstream>
#include "rooms.h"

Rooms::Rooms() {
    north = south = east = west = -1;
    enemy = NULL;
    ASCIIRoomArt = "";
}

Rooms::~Rooms() {
    delete enemy;
}

const std::string Rooms::getASCIIRoomArt() {
    return ASCIIRoomArt;
}

void Rooms::createEnemy(std::string enemyName, std::string enemyDialogue, std::string ASCIIEnemyArt, int HP, int atk) {
    enemy = new Enemies(enemyName, enemyDialogue, ASCIIEnemyArt,HP, atk);
    return;
}

void Rooms::deleteEnemy() {
    delete enemy;
    enemy = NULL;
    return;
}