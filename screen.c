#include "screen.h"
#include <stdio.h>
#include <stdlib.h>


static List* messages;
static pthread_mutex_t* semaphorePointer;
static pthread_t screenThread;

void* print_screen_procedure(void* args);
void start_screen_thread();

pthread_t* screen_init(List* receivedMessages, pthread_mutex_t* semaphorePtr) {
    semaphorePointer = semaphorePtr;
    messages = receivedMessages;
    start_screen_thread();
    return &screenThread;
}

void start_screen_thread() {
    int pthread_creation_status = pthread_create(
            &screenThread,
            NULL,
            print_screen_procedure,
            NULL
    );
    if(pthread_creation_status != 0) {
        printf("An error has occurred in screen.start_screen_thread() while creating a thread.");
        return;
    }
}

void* print_screen_procedure(void* args) {
    while(1) {
        pthread_mutex_lock(semaphorePointer);
        {
            if(List_count(messages) > 0) {
                {
                    char* message = List_remove(messages);
                    printf("Received message is: %s \n", message);
                    free(message);
                }

            }
        }
        pthread_mutex_unlock(semaphorePointer);
        //Block the access to received_messages from the other thread (receiver)
        }

}



