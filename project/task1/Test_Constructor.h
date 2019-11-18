#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

using namespace std;

class character
{
public:
    int x, y;
    int mx, my;
    int role;
    int health;
    char name[200] = {0};

    void init(int new_role, char character_name[], int new_x, int new_y, int new_health)
    {
        role = new_role;
        x = new_x;
        y = new_y;
        health = new_health;
        strcpy(name, character_name);
    }
};