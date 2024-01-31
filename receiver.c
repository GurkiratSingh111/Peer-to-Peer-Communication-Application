#include "receiver.h"
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_MESSAGE_LEN 256

static struct sockaddr_in sin;
static int socketDescriptor;
static pthread_t receiverThread;
static pthread_mutex_t* semaphorePointer;
static List* messages;
static bool isCancelled;

void setup_sin(unsigned short LOCAL_PORT);
int create_and_bind_socket();
void* receive_thread_procedure(void* args);

pthread_t* receiver_init(unsigned short LOCAL_PORT, List* receivedMessages, pthread_mutex_t* semaphorePtr) {
    isCancelled = false;
    setup_sin(LOCAL_PORT);
    socketDescriptor = create_and_bind_socket();
    semaphorePointer = semaphorePtr;
    messages = receivedMessages;
    printf("Successfully running on port %d \n", LOCAL_PORT);

    int pthread_creation_status = pthread_create(
            &receiverThread,
            NULL,
            receive_thread_procedure,
            NULL
            );
    if(pthread_creation_status != 0) {
        printf("An error has occurred in receiver.receiver_init() while creating a thread.");
        return NULL;
    }


    return &receiverThread;
}

//void receiver_shutdown() {
//    pthread_cancel(receiverThread);
//    pthread_join(receiverThread, NULL);
//}

void setup_sin(unsigned short LOCAL_PORT) {
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(LOCAL_PORT);
}

int create_and_bind_socket() {
    int socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    if(socketDescriptor == -1) {
        printf("Could not create the socket at receiver.create_and_bind_socket()");
        return -1;
    }
    int bind_status = bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));
    if(bind_status == -1) {
        printf("Could not bind the socket at receiver.create_and_bind_socket()");
        return -1;
    }
    return socketDescriptor;
}

// Receive the message, add it to the linked list as a producer, check if it's == "!", stop if yes.
void* receive_thread_procedure(void* args) {
    while(1) {
        struct sockaddr_in sinRemote;
        unsigned int sin_len = sizeof(sinRemote);
//        char messageRx[MAX_MESSAGE_LEN];
        char* messageRx = (char*) (malloc(sizeof(char) * MAX_MESSAGE_LEN));
        int bytesRx = recvfrom(socketDescriptor, messageRx, MAX_MESSAGE_LEN, 0, (struct sockaddr*) &sinRemote, &sin_len);


        int terminateIdx=  (bytesRx < MAX_MESSAGE_LEN)? bytesRx - 1: MAX_MESSAGE_LEN - 1;
        messageRx[terminateIdx] = '\0';

        if(strcmp(messageRx, "!") == 0) {
            isCancelled = true;
            printf("TERMINATION STRING HAS BEEN RECEIVED!");
            cancel_threads(false);
            break;
        }


        pthread_mutex_lock(semaphorePointer);
        {
            List_prepend(messages, messageRx);
        }
        pthread_mutex_unlock(semaphorePointer);

    }
    pthread_cancel(receiverThread);
    exit(0);

}


