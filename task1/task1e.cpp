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

    for(auto i:players) {
        *i.name = "newname";
        cout << "Name: " << players[0].name;
    }
/*
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
*/

    //print(players);

    /*do{
        string text;
        
        for(auto it:players) {
            string name;
            int role, x, y, health;
            cout << "Input player name: ";
            cin >> name;
            text = "Name: ";
            //it.name = name;
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

            const char *line = text.c_str();

            nBytes = strlen(line) + 1;
            sendto(clientSocket, line, nBytes, 0, (struct sockaddr *)&ServerAddr, addr_size);
        }
    } while(strncmp(line, "Quit", strlen(line) - 1) != 0);

*/
/*
        string text;

        text = "Name: " + it.name + "\nRole: " + (string)it.role 
                + "\nCoordinates: (" + it.x + "," + it.y + ")"
                + "\nHealth: " + it.health; 

        nBytes = sizeof(text) + 1;
        sendto(clientSocket, input_buffer, nBytes, 0, (struct sockaddr *)&ServerAddr, addr_size);
        }
    do
    {
        cout << "Type a sentence to send to the server: ";
        cin.getline(input_buffer, 1023, '\n');
        nBytes = strlen(input_buffer) + 1;
        sendto(clientSocket, input_buffer, nBytes, 0,
                (struct sockaddr *)&ServerAddr, addr_size);
    } while (strncmp(input_buffer, "Quit", strlen(input_buffer) -1) != -0);
    return 0;
    */
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