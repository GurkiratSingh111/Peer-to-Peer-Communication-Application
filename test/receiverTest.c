#include "receiverTest.h"
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_MESSAGE_LEN 1024
#define PORT 22110

static pthread_t receiverThread;

void* receiveThreadProcedure(void* port);

void receiver_init() {


    pthread_create(
            &receiverThread,
            NULL,
            receiveThreadProcedure,
            NULL);
    printf("CREATING A THREAD!");
}
void receiver_shutdown() {
    pthread_cancel(receiverThread);
    pthread_join(receiverThread, NULL);
}

void* receiveThreadProcedure(void* port) {
    printf("RUNNIN!");
    int* intPort = port;

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);

    int socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));

    while(1) {
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
        char messageRx[MAX_MESSAGE_LEN];
        int bytesRx = recvfrom(socketDescriptor, messageRx, MAX_MESSAGE_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);

        int terminateIdx=  (bytesRx < MAX_MESSAGE_LEN)? bytesRx - 1: MAX_MESSAGE_LEN - 1;
        messageRx[terminateIdx] = '\0';

        printf("\n %s \n ", messageRx);
    }
}