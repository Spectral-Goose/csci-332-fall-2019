#define _GNU_SOURCE /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <pthread.h>
#include "Character.h"
#include "League.h"
#include "networkHelper.h"

using namespace std;

character *myCharacter, *newPlayer;
std::vector<character *> gamers;
SDL_Renderer *renderer;
SDL_Window *window;
bool quit = false;
pthread_mutex_t received_message_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t vector_lock = PTHREAD_MUTEX_INITIALIZER;
int x, y;
int clientSocket, portNum, nBytes;
char input_buffer[1024] = {0};
char received_msg[1024] = {0};
struct sockaddr_in ServerAddr;
socklen_t addr_size;
const int listeningPort = 12345;

char broadcastAddress[17] = {0};
char My_IP[17] = {0};
// ToDo: Create a broadcast permission integer variable
int broadcastPermission = 1;

// ToDo: Creating a variable to hold where the player hit is
int playerHitIndex = 0;

void draw_text(SDL_Renderer *renderer, int x, int y, char message[], SDL_Color color, int alignment)
{
    SDL_Rect text_rect;
    SDL_Surface *messageSurface;
    int message_width;
    int message_height;
    SDL_Texture *textTexture;

    TTF_Font *Sans = TTF_OpenFont("FreeSans.ttf", 12); //this opens a font style and sets a size
    TTF_SizeText(Sans, message, &message_width, &message_height);
    messageSurface = TTF_RenderText_Blended(Sans, message, color);
    TTF_CloseFont(Sans);
    switch (alignment)
    {
    case alignLeft:
        text_rect.x = x; //controls the rect's x coordinate
        break;
    case alignCenter:
        text_rect.x = x - (message_width / 2); //controls the rect's x coordinate
        break;
    case alignRight:
        text_rect.x = x - message_width; //controls the rect's x coordinate
        break;
    }
    text_rect.y = y;              // controls the rect's y coordinte
    text_rect.w = message_width;  // controls the width of the rect
    text_rect.h = message_height; // controls the height of the rect
    textTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
    SDL_DestroyTexture(textTexture);
}

void draw_title(SDL_Renderer *renderer, int y, char message[], SDL_Color color)
{
    SDL_Rect text_rect;
    SDL_Surface *messageSurface;
    int message_width;
    int message_height;
    SDL_Texture *textTexture;
    SDL_Rect r;

    //Clear background of text

    TTF_Font *Sans = TTF_OpenFont("FreeSans.ttf", 48); //this opens a font style and sets a size
    TTF_SizeText(Sans, message, &message_width, &message_height);
    messageSurface = TTF_RenderText_Shaded(Sans, message, Black, White);
    TTF_CloseFont(Sans);
    text_rect.x = 512 - (message_width / 2); //controls the rect's x coordinate
    text_rect.y = y;                         // controls the rect's y coordinte
    text_rect.w = message_width;             // controls the width of the rect
    text_rect.h = message_height;            // controls the height of the rect
    r.x = 0;
    r.y = y;
    r.w = 1024;
    r.h = message_height;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &r);

    textTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
    SDL_DestroyTexture(textTexture);
}

int Choosing_Role()
{
    bool done = false;
    SDL_Event event;
    int role;

    //Render Roles
    SDL_Rect rect[6];
    SDL_Surface *imageSurface;
    SDL_Texture *image[6];
    int x, y;

    for (role = 0; role < 6; role++)
    {
        switch (role)
        {
        case 0:
            imageSurface = SDL_LoadBMP("c1.bmp");
            break;
        case 1:
            imageSurface = SDL_LoadBMP("c2.bmp");
            break;
        case 2:
            imageSurface = SDL_LoadBMP("c3.bmp");
            break;
        case 3:
            imageSurface = SDL_LoadBMP("c4.bmp");
            break;
        case 4:
            imageSurface = SDL_LoadBMP("c5.bmp");
            break;
        case 5:
            imageSurface = SDL_LoadBMP("c6.bmp");
            break;
        }
        image[role] = SDL_CreateTextureFromSurface(renderer, imageSurface);
        rect[role].h = 70;
        rect[role].w = 70;
        rect[role].x = 262 + 100 * role;
        rect[role].y = 314;
    }

    SDL_RenderClear(renderer);
    char message[100];
    strcpy(message, "Please Choose Your Role");
    draw_title(renderer, 100, message, Black);

    for (int i = 0; i < 6; i++)
    {
        SDL_RenderCopy(renderer, image[i], NULL, &rect[i]);
    }
    SDL_RenderPresent(renderer);

    while (!done)
    {
        while (!done && SDL_WaitEvent(&event))
        {
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                role = -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    if ((mouseX > 262) && (mouseX < 862))
                    {
                        role = (mouseX - 262) / 100;
                        done = true;
                    }
                    break;
                }
            }
        }
    }
    return role;
}

int Choosing_Name(char name[])
{
    bool done = false;
    SDL_Event event;
    int len = 0;

    //Render Roles
    SDL_Rect rect[6];
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    char lowerCase[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char upperCase[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char numeric[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int x, y;

    SDL_RenderClear(renderer);
    char message[100];
    strcpy(message, "Please Enter Your Name");
    draw_title(renderer, 100, message, Black);

    len = 0;
    while (!done)
    {
        SDL_Delay(20);
        while (!done && SDL_WaitEvent(&event))
        {
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                return -1;
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    name[len++] = ' ';
                    name[len] = 0;
                    break;
                case SDLK_BACKSPACE:
                    if (len > 0)
                        len--;
                    name[len] = 0;
                    break;
                case SDLK_RETURN:
                    done = true;
                    break;
                default:
                    int key = event.key.keysym.sym;
                    if ((key >= 97) && (key <= 122))
                    {
                        if (event.key.keysym.mod & KMOD_SHIFT)
                            name[len++] = upperCase[event.key.keysym.sym - 97];
                        else
                            name[len++] = lowerCase[event.key.keysym.sym - 97];
                        name[len] = 0;
                    }
                    if ((key >= 48) && (key <= 57))
                    {
                        name[len++] = numeric[event.key.keysym.sym - 48];
                        name[len] = 0;
                    }
                }
                break;
            }
            draw_title(renderer, 200, name, Black);
            SDL_RenderPresent(renderer);
        }
    }
    return 0;
}

int init()
{
    // initialize random seed
    srand(time(NULL));

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("CSCI332 Final Project Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    //ToDo: Initialize clientSocket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, 
        sizeof(broadcastPermission));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(12345);
    
    //ToDo: Call broadcastAddr and IPaddr respectively
    strcpy(broadcastAddress, Broadcast_Address());
    strcpy(My_IP, IPAddress());
    
    ServerAddr.sin_addr.s_addr = inet_addr(broadcastAddress);
    addr_size = sizeof(ServerAddr);
    

    // ToDo: Get my computer's lan state

    return 0;
}

void *receiveMessage(void *ptr) // Server Thread
{
    // ToDo: Initialize a server socket
    int udpSocket;
    int clientAddr;

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = listeningPort;
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    memset(ServerAddr.sin_zero, '\0', sizeof ServerAddr.sin_zero);
    bind(udpSocket, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
    socklen_t addr_size = sizeof clientAddr;

    // ToDo: Create a loop and parse the received message
    /*char str[] = "Update,192.168.1.117,Name,0,0,0,0";
    char * pch;
    printf("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok(ptr,",");
    pch = strtok(NULL,",");

    while(pch != NULL) {
        printf("%s\n",pch);
        pch = strtok(NULL,",");
    }*/
    
    do {
        char *messageType = strtok(ptr,",");
        char *ip = strtok(NULL,",");
        char *name = strtok(NULL,",");
        char *role = strtok(NULL,",");
        char *x = strtok(NULL,",");
        char *y = strtok(NULL,",");
        char *health = strtok(NULL,",");
        // Update message syntax: Update, IP, Name, Role, newX, newY, NewHealth
    //Update
        
        if(messageType == "Update") {
            bool found = false;
            for(auto it:gamers) {
                if(it->IP == ip) {
                found = true;
                    it->x = x;
                    it->y = y;
                }
            }
    // ToDo: For Update, check if the IP is in the vector, if not add the player to the vector.
            if(!found) {
                character newChar = new character(ip, (int)role, name, (int)x, (int)y, (int)health);
                gamers.push_back(newChar);
            }
    //       otherwise,
        }
        // Hit message syntax: Hit, IP
    //Hit
    // ToDo: If the hit message is for you, reduce your character's health by 5 points.
        else if(messageType == "Hit") {
            if(ip == My_IP) {
                myCharacter->health -= 5;
    //      If your health reduces to 0 or less, notify main thread with a flag so the main thread will broadcast
    //      QuitGame message to other players
                if(myCharacter->health <= 0) {
                    send_message(QuitGame);
                }
            }
        }
        // QuitGame message syntax: Quit
    //QuitGame
    // ToDo:
    // 1. Use a for loop to find the player who wants to exit the game.
    // 2. Remove it from gamers vector        
        else if(messageType == "QuitGame") {
            for(int i = 0; i < gamers.size(); ++i) {
                if(strncmp(gamers[i]->IP, character->IP) == 0) {
                    gamers->remove(i);
                }
            }
        }
    } while(strncpm(buffer, "Quit", strlen(buffer) - 1) != 0);
}

void send_message(ActionType action)
{
    char buffer[1024] = {0};
    bool Do_Actions = true;

    switch (action)
    {
    case Hit:
        // ToDo:
        // Send a Hit message and player IP
        
        sprintf(buffer, "Hit, %s", gamers[playerHitIndex]->IP);
        
        break;
    case Update:
        // ToDo:
        // 1. Send a Update message with IP, name, Role, location and health

        sprintf(buffer, "Update,%s,%s,%d,%d,%d,%d", myCharacter->IP, myCharacter->name, myCharacter->role,
            myCharacter->x, myCharacter->y, myCharacter->health);

        break;
    case QuitGame:
        // ToDo:
        // Send a Quit message and player IP

        sprintf(buffer, "Quit");

        break;
    default:
        Do_Actions = false;
    }
    if (Do_Actions)
    {
        // ToDo:
        nBytes = sizeof(buffer) + 1;

        sendto(clientSocket, buffer, nBytes, 0, 
        (struct sockaddr *)&ServerAddr, addr_size);
    }
}

bool checkOverlap(int x1, int y1, int x2, int y2) {
    // Hitbox  tl = (x1,y1), tr = (x1+30,y1), bl = (x1,y1-30), br = (x1+30,y1)
    // Charbox tl = (x2,y2), tr = (x2+70,y2), bl = (x2,y2-70), br = (x2+70,y2)
    int hbleft = x1;
    int hbright = x1 + 30;
    int hbtop = y1;
    int hbbot = y1 + 30;

    int cbleft = x2;
    int cbright = x2 + 70;
    int cbtop = y2;
    int cbbot = y2 + 70;

    if(hbleft > cbright) {
        cout << "1";
        return false;
    } 
    if(hbright < cbleft) {
        cout << "2";
        return false;
    }
    if(hbtop > cbbot) {
        cout << "hbtop" << hbtop << "\n";
        cout << "cbbot" << cbbot << "\n";
        cout << "3";
        return false;
    }
    if(hbbot < cbtop) {
        cout << "4";
        return false;
    }

    return true;
}

int event_thread(void *arg)
{
    SDL_Event event;
    ActionType action = None;

    // declare hitbox x and y and enemy x and y
    int hx, hy, ex, ey;

    while (!quit)
    {
        while (!quit && SDL_WaitEvent(&event))
        {
            SDL_PollEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                action = QuitGame;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    //fight left
                    hx = myCharacter->x - 30;
                    hy = myCharacter->y + 20;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the left hand side
                    // 2. If there is a player
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_d:
                    // fight right
                    hx = myCharacter->x + 70;
                    hy = myCharacter->y + 20;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_w:
                    // fight up
                    hx = myCharacter->x + 20;
                    hy = myCharacter->y - 30;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_x:
                    //fight down
                    hx = myCharacter->x + 20;
                    hy = myCharacter->y + 70;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_q:
                    // fight upper left
                    hx = myCharacter->x - 30;
                    hy = myCharacter->y - 30;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_e:
                    //fight upper right
                    hx = myCharacter->x + 70;
                    hy = myCharacter->y - 30;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_z:
                    // fight lower left
                    hx = myCharacter->x - 30;
                    hy = myCharacter->y + 70;
                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_c:
                    // fight lower right
                    hx = myCharacter->x + 70;
                    hy = myCharacter->y + 70;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_s:
                    // fight overlapped
                    hx = myCharacter->x + 20;
                    hy = myCharacter->y + 20;

                    // ToDo:
                    // 1. go Through every element in the gamers vector and see if any player at the right hand side
                    // 2. If there is a player, set proper action
                    // 3. No, ignore it
                    // 4. Yes, send hit to the player
                    for(int i = 0; i < gamers.size(); i++) {
                        action = Hit;
                        if(checkOverlap(hx, hy, gamers[i]->x, gamers[i]->y)) {
                            playerHitIndex = i;
                            send_message(action);
                        }
                    }
                    break;
                case SDLK_ESCAPE: // Quitting game
                    quit = true;
                    action = QuitGame;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    myCharacter->move(mouseX, mouseY);
                    action = Move;
                    break;
                }
            }
        }
        send_message(action);
        exit(0);
    }
    return 0;
}

int main(int argc, char **argv)
{ 
    // variables
    char name_string[100] = {0};
    char temp_string[255] = {0}; // Maximum length of a string
    int myRole = 0;
    bool quit = false;
    SDL_Event event;
    int center_x, top_y;
    ActionType action;

    init();

    myRole = Choosing_Role();
    if (myRole == -1)
        return -1;
    if (Choosing_Name(name_string) == -1)
        return -1;

    // Initiaize threads
    SDL_Thread *thread;
    thread = SDL_CreateThread(event_thread, "Test", NULL);
    pthread_t receiveThread;
    int iret1;
    iret1 = pthread_create(&receiveThread, NULL, &receiveMessage, NULL);
    if (iret1)
    {
        fprintf(stderr, "Error - pthread_create() creturn code: %d\n", iret1);
        exit(EXIT_FAILURE);
    }
    myCharacter = new character(renderer, My_IP, myRole, name_string);
    while (!quit)
    {
        SDL_Delay(33);
        myCharacter->update();
        send_message(Update);
        SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255); // Background color as green
        SDL_RenderClear(renderer);

        // For your debugging....
        // Uncomment the next two lines anc change the message you want to debug
        // sprintf(temp_string, "x: %d, y: %d", myCharacter->get_x(), myCharacter->get_y());
        // draw_text(renderer, 0, 0, temp_string, Black,alignLeft);
        // sprintf(temp_string, "IP:%s Netmask:%s Broadcast:%s", IPAddress(), net_mask(), broadcastAddress());
        // draw_text(renderer, 0, 0, temp_string, Black, alignLeft);
        draw_text(renderer, 0, 0, received_msg, Black, alignLeft);
        for (auto &p : gamers)
        {
            SDL_RenderCopy(renderer, p->image, NULL, &p->rect);            //Role image
            SDL_RenderCopy(renderer, p->textTexture, NULL, &p->text_rect); //Name of the player
            center_x = p->get_x() + (p->get_w() / 2);
            top_y = p->get_y() + p->get_h() + 12;
            sprintf(temp_string, "%d", p->health);
            draw_text(renderer, center_x, top_y, temp_string, Red, alignCenter);
        }
        SDL_RenderPresent(renderer);
    }

    close(clientSocket);
    vector<character *>().swap(gamers); // Clear gamers vector
    // cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
