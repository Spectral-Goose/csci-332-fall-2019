#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>
#include "Test_Constructor.h"

using namespace std;

int main(int argc, char const *argv[]) {
    vector<character> Characters;
    for(int i = 0; i < 3; i++) {
        cout << "===="
             << "enter character information"
             << "===="
             << "\n";
        char Name[200];
        cout << "Enter Name: ";
        cin >> Name;
        cout << "Enter Role: ";
        int Role;
        cin >> Role;
        cout << "Enter X: ";
        int x, y;
        cin >> x;
        cout << "Enter Y: ";
        cin >> y;
        int Health;
        cout << "Enter Health: ";
        cin >> Health;

        character NewCharacter;
        NewCharacter.init(Role, Name, x, y, Health);

        Characters.push_back(NewCharacter);
    }

    for(int i = 0; i < Characters.size(); i++) {
        cout << "\n"
             << "-------------"
             << "\n";
        cout << "Name: "
             << Characters[i].name << "\n";

        cout << "Health: "
             << Characters[i].health << "\n";
         
        cout << "Role: "
             << Characters[i].role << "\n";

        cout << "Coordinates: (" << Characters[i].x << "," << Characters[i].y << ")";
    }
    return 0;
}