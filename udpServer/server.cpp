#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

int main() 
{
    int udpSocket, nBytes;
    char buffer[1024];
    struct sockaddr_in ServerAddr, ClientAddr;
    char *ClientIP;
    


    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    ServerAddr.sin_family = AF_INET;
    cout << "Please enter your listening port: ";
    cin >> buffer;
    ServerAddr.sin_port = htons(atoi(buffer));
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    memset(ServerAddr.sin_zero, '\0', sizeof(ServerAddr.sin_zero));
    bind(udpSocket, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
    socklen_t addr_size = sizeof ClientAddr;
    do {
        nBytes = recvfrom(udpSocket, buffer, 1024, 0,
                            (struct sockaddr *)&ClientAddr, &addr_size);

        ClientIP = inet_ntoa(ClientAddr.sin_addr);
        cout << inet_ntoa(ClientAddr.sin_addr) << " says: " << buffer << endl;
    } while (strncmp(buffer, "Quit", strlen(buffer) - 1) != 0);
    return 0;
}