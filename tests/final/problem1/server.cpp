#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctime>

using namespace std;

int main() 
{
    int udpSocket, nBytes;
    char buffer[1024];
    struct sockaddr_in ServerAddr, ClientAddr;
    char *ClientIP;
    int clientSocket;
    const int listeningPort = 56789;
    char broadcastAddress[17] = {0};
    char My_IP[17] = {0};
    int broadcastPermission = 1;

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(56789);
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    memset(ServerAddr.sin_zero, '\0', sizeof(ServerAddr.sin_zero));
    bind(udpSocket, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
    socklen_t addr_size = sizeof ClientAddr;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, 
        sizeof(broadcastPermission));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(12345);
    
    //ToDo: Call broadcastAddr and IPaddr respectively
    char *Broadcast_Address = (char *)"127.0.0.1";
    char *IPAddress = (char *)"127.0.0.1";
    strcpy(broadcastAddress, Broadcast_Address);
    strcpy(My_IP, IPAddress);
    
    ServerAddr.sin_addr.s_addr = inet_addr(broadcastAddress);
    addr_size = sizeof(ServerAddr);

    do {
        char empty[200] = "1";
        buffer = empty;
        nBytes = recvfrom(udpSocket, buffer, 1024, 0,
                            (struct sockaddr *)&ClientAddr, &addr_size);

        ClientIP = inet_ntoa(ClientAddr.sin_addr);
        cout << inet_ntoa(ClientAddr.sin_addr) << " says: " << buffer << endl;

        if(strncmp(buffer, "WHO", sizeof("WHO")) == 0) {
            cout << "Name: Taylor Singleton, ID: 189561\n";
        }
        else if(strncmp(buffer, "TIME", sizeof("TIME")) == 0) {
            cout << "Sun Dec 8 19:01:54";
        }
        else if(strncmp(buffer, "HELLO", sizeof("HELLO")) == 0) {
            cout << "HELLO";
        }
        else {
            cout << "Unknown Command\n";
        }

    } while (strncmp(buffer, "BYE", strlen(buffer) - 1) != 0);
    return 0;
}