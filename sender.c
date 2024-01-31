#include "sender.h"
#include <arpa/inet.h>

static struct sockaddr_in sinRemote;
static int socketDescriptor;
static pthread_t senderThread;
static pthread_mutex_t* semaphorePointer;
static List* messages;
static bool isCancelled;

void setup_remote_sin(unsigned short REMOTE_PORT, char* REMOTE_IP);
int sender_bind_socket();
void* send_thread_procedure(void* args);

pthread_t* sender_init(unsigned short REMOTE_PORT, char* REMOTE_IP, List* messagesToBeSent, pthread_mutex_t* semaphorePtr) {
    isCancelled = false;
    setup_remote_sin(REMOTE_PORT, REMOTE_IP);
    sender_bind_socket();
    messages = messagesToBeSent;
    semaphorePointer = semaphorePtr;

    int pthread_creation_status = pthread_create(
            &senderThread,
            NULL,
            send_thread_procedure,
            NULL
    );
    if(pthread_creation_status != 0) {
        printf("An error has occurred in receiver.receiver_init() while creating a thread.");
        return NULL;
    }
    return &senderThread;
}

void setup_remote_sin(unsigned short REMOTE_PORT, char* REMOTE_IP) {
    memset(&sinRemote, 0, sizeof(sinRemote));
    sinRemote.sin_family = AF_INET;
    sinRemote.sin_addr.s_addr = inet_addr(REMOTE_IP);
    sinRemote.sin_port = htons(REMOTE_PORT);
}

int sender_bind_socket() {
    socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);
    if(socketDescriptor == -1) {
        printf("Could not create the socket at sender.sender_bind_socket() \n");
        return -1;
    }

}

void* send_thread_procedure(void* args) {
    while(1) {
        pthread_mutex_lock(semaphorePointer);
        {
            if(List_count(messages) > 0) {
                char* message = List_remove(messages);
//                send(socketDescriptor, message, strlen(message) + 1, 0);
                sendto(socketDescriptor, message, strlen(message) + 1, 0, (struct sockaddr*) &sinRemote, sizeof (sinRemote));
                printf("THIS MESSAGE HAS BEEN SENT: %s\n", message);

                if(strcmp(message, "!") == 0) {
                    isCancelled = true;
                    printf("Stopping the host program! %s \n", message);
                    cancel_threads(true);
                    free(message);
                    pthread_mutex_unlock(semaphorePointer);
                    break;
                }

                free(message);
            }
        }
        pthread_mutex_unlock(semaphorePointer);
    }
    pthread_cancel(senderThread);
    exit(0);
}


