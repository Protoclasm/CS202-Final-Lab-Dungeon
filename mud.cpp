#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include "rooms.h"
#include "player.h"
#include "bag.h"
#include "enemies.h"

void setExit(Rooms &room, const char direction, const int roomIndex) {
    switch(direction)
    {
        case 'n':
            room.north = roomIndex;
            break;
        case 's':
            room.south = roomIndex;
            break;
        case 'e':
            room.east = roomIndex;
            break;
        case 'w':
            room.west = roomIndex;
            break;
    }
    return;
}

void stripWhitespace(std::string &str) {
    while (isspace(str.back())) {
        str.pop_back();
    }
    while (isspace(str.front())) {
        str.erase(str.begin());
    }
    return;
}

Rooms *loadRooms(const std::string dungeonFilename) 
{
    std::ifstream fin(dungeonFilename);
    //Following if-statement checks for any file opening errors.
    if(!(fin.is_open()))
    {
        std::cerr << "Error: File did not open correctly" << std::endl;
        exit(1);
    }

    size_t tildeCount = 0; //# of tildes inside file. 8 for each room.
    std::string stringHolder; //Holds strings for counting # of tildes.
    while(getline(fin, stringHolder, '~')) tildeCount++; //Finds total of tildes inside file.
    
    //Calculates # of rooms. CHANGE DENOMINATOR TO HOWEVER MANY ARE NEEDED. I PUT 6, ONE PER READ IN (art counts as 2 because of enemy and room art).
    size_t roomCount = tildeCount / 8;

    Rooms *rooms = new Rooms[roomCount];

    //Following two lines jumps back to beginning of file.
    fin.clear();
    fin.seekg(0);

    //Reads in and stores the room's title, description, exits, enemy data, and arts.
    //TODO: ADD READING IN THE ARTS AND ENEMY.
    for (size_t i = 0; i < roomCount; i++) {
        //Following four lines read and store the name and description then removes extra whitespaces.
        getline(fin, rooms[i].name, '~');
        stripWhitespace(rooms[i].name);
        getline(fin, rooms[i].description, '~');
        stripWhitespace(rooms[i].description);

        //Rest of code is for exits and enemy data/arts.
        std::string exits, enemyName, stats, ASCIIEnemyArt, dialogue; //For reading in the exits.
        getline(fin, exits, '~');
        stripWhitespace(exits);
        std::istringstream sin(exits);
        char direction; //Direction of the exit.
        int room_index; //Rooms the exit leads to.
        while(sin >> direction >> room_index) setExit(rooms[i], direction, room_index); //Reads in the direction/index and sets the room exits.
        sin.clear(); //Clears istringstream for use again.
        getline(fin, rooms[i].ASCIIRoomArt, '~');
        getline(fin, enemyName, '~');
        stripWhitespace(enemyName);
        int HP, ATK;
        getline(fin, stats, '~');
        stripWhitespace(stats);
        std::istringstream enemyStats(stats);
        enemyStats >> HP >> ATK;
        // std::cout << HP << "Enemy #" << i << "'s HP" << std::endl; //For testing if HP is being correctly stored.
        enemyStats.clear();
        getline(fin, ASCIIEnemyArt, '~');
        getline(fin, dialogue, '~');
        //Read in EVERYTHING about the enemy first. If enemyName ! empty, create enemy with all read in values. Else, do not create enemy.
        if (!enemyName.empty()) rooms[i].createEnemy(enemyName, dialogue, ASCIIEnemyArt, HP, ATK);

    }

    //dumpRoomss(rooms, roomCount); //Uncomment for debugging.

    fin.close();
    return rooms;
}


int main(int argc, char *argv[]) {
    if(2 != argc) {
        std::cerr << "Usage: ./mud fileName" << std::endl;
        return 1;
    }

    Rooms *rooms = loadRooms(argv[1]); //This also checks for whether the file is openable.

    Player player;
    Bag bag;
    player.decisions(bag, rooms);

    // std::cout << player.getAttack() << ' ' << player.getHP() << std::endl;
    //int currentRooms = 0;
    // std::vector<std::vector<Rooms> > dungeon(sizeOfDungeon, std::vector<Rooms>(sizeOfDungeon)); //Each position corresponds to a new room.
    //std::vector<std::vector<std::string> > dungeon(sizeOfDungeon, std::vector<std::string>(sizeOfDungeon, "st")); This is how to make a 2D sized array of strings.
    // for(int i = 0; i < sizeOfDungeon; i++) {
    //     for(int j = 0; j < sizeOfDungeon; j++) {
    //         std::cout << dungeon[i][j].name;
    //     }
    //     std::cout << std::endl;
    // }
    // delete rooms;
    return 0;
}