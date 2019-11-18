#include <iostream>
#include <pthread.h>

using namespace std;

void *print_message(void *ptr) {
    char *messages;

    messages = (char *)ptr;
    printf("%s \n", messages);
}

int main() {
    pthread_t t1, t2;

    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";
    int ret1, ret2;

    ret1 = pthread_create(&t1, NULL, print_message, (void *)message1);
    ret2 = pthread_create(&t2, NULL, print_message, (void *)message2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    exit(EXIT_SUCCESS);
}