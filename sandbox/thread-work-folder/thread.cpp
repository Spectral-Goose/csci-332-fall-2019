#include <iostream>
#include <pthread.h>

using namespace std;

int COM = 0;
pthread_mutex_t COMLock;

void *increaseOne(void *ptr) {
    char *messages;

    messages = (char *)ptr;
    do {
        pthread_mutex_lock(&COMLock);
        cout << messages << " " << COM << endl;
        COM++;
        pthread_mutex_unlock(&COMLock);
    } while(COM < 60000);
}

void *increaseTwo(void *ptr) {
    char *messages;

    messages = (char *)ptr;
    do {
        pthread_mutex_lock(&COMLock);
        cout << messages << " " << COM << endl;
        COM++;
        pthread_mutex_unlock(&COMLock);
    } while(COM < 60000);
} 

int main() {
    pthread_t t1, t2;

    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int ret1, ret2;

    ret1 = pthread_create(&t1, NULL, increaseOne, (void *)message1);
    ret2 = pthread_create(&t2, NULL, increaseTwo, (void *)message2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    exit(EXIT_SUCCESS);
}