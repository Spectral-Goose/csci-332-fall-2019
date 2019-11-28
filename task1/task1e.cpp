#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "Test_Constructor.h"

using namespace std;

void print(vector<character> vec);

int main() 
{
    int clientSocket, portNum, nBytes;
    char input_buffer[1024], port_string[10], ip_string[17];
    struct sockaddr_in ServerAddr;
    socklen_t addr_size;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    ServerAddr.sin_family = AF_INET;
    cout << "Please enter the server port: ";
    cin.getline(port_string, 9, '\n');
    portNum = atoi(port_string);
    ServerAddr.sin_port = htons(portNum);
    cout << "Please enter the server IP: ";
    cin.getline(ip_string, 16, '\n');
    ServerAddr.sin_addr.s_addr = inet_addr(ip_string);
    memset(ServerAddr.sin_zero, '\0', sizeof ServerAddr.sin_zero);
    addr_size = sizeof ServerAddr;

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

        const char *line;
    do {
    for(auto it:players) {
        string text;
        text = "Name: ";
        text += it.name;
        text += ", Role: ";
        text += to_string(it.role);
        text += ", Coordinates: (";
        text += to_string(it.x);
        text += ",";
        text += to_string(it.y);
        text += ")";
        text += ", Health: ";
        text += to_string(it.health);
        text += "\n";

        line = text.c_str();

        cout << "name: " << line << "\n";
        nBytes = strlen(line) + 1;
                sendto(clientSocket, line, nBytes, 0, (struct sockaddr *)&ServerAddr, addr_size);
        
    }
    } while(strncmp(line, "Quit!", strlen(line)-1) != 0);
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