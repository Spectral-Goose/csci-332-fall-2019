#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include "Test_Constructor.h"

using namespace std;

void print(vector<character> vec);

int main() {

    vector<character> players;

    // Syntax: character(ROLE, CHARACTER NAME, X CORD, Y CORD, HEALTH)
    character dps, tank, caster;

    char name1[200] = "Rogue";
    char name2[200] = "Tank";
    char name3[200] = "Wizard";

    dps.init(0, name1, 25, 10, 500);
    players.push_back(dps);

    tank.init(1, name2, 50, 30, 750);
    players.push_back(tank);

    caster.init(2, name3, 32, 41, 450);
    players.push_back(caster);

    print(players);    

    char keyword[200];    

    cout << "Enter a player name to find: ";
    cin >> keyword;
    cout << "\n";

    int count = 0;

    if(keyword == "Quit!") {
        return 0;
    }

    for(auto it:players) {
        count++;
        if(strcmp(it.name, keyword) == 0) {
            int newRole, newX, newY, newHealth;
            string line;

            cout << "Enter a new Role: ";
            cin >> line;
            if(line == "Quit!") {
                return 0;
            }
            else {
                newRole = stoi(line);
            }

            cout << "\nEnter a new X-coordinate: ";
            cin >> line;
            if(line == "Quit!") {
                return 0;
            }
            else {
                newX = stoi(line);
            }

            cout << "\nEnter a new Y-coordinate: ";
            cin >> line;
            if(line == "Quit!") {
                return 0;
            }
            else {
                newY = stoi(line);
            }

            cout << "\nEnter a new Health amount: ";
            cin >> line;
            if(line == "Quit!") {
                return 0;
            }
            else {
                newHealth = stoi(line);
            }

            cout << "\n";

            players[count-1].role = newRole;
            players[count-1].x = newX;
            players[count-1].y = newY;
            players[count-1].health = newHealth;
        }
        else if(count == 3) {
            cout << "No players with that name were found.\n";
        }
    }

    print(players);

    return 0;
}

void print(vector<character> vec) {
    for(auto it:vec) {
        cout << "Name: " << it.name << "\n";
        cout << "Role: " << it.role << "\n";
        cout << "Coordinates: (" << it.x << "," << it.y << ")\n";
        cout << "Health: " << it.health << "\n\n";
    }
}