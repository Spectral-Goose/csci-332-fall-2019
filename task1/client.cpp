#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;

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

    do
    {
        cout << "Type a sentence to send to the server: ";
        cin.getline(input_buffer, 1023, '\n');
        nBytes = strlen(input_buffer) + 1;
        sendto(clientSocket, input_buffer, nBytes, 0,
                (struct sockaddr *)&ServerAddr, addr_size);
    } while (strncmp(input_buffer, "Quit", strlen(input_buffer) -1) != -0);
    return 0;
}