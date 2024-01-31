#include <stdio.h>
#include <stdlib.h>
#include "receiver.h"
#include "list.h"
#include <pthread.h>
#include "screen.h"
#include "keyboard.h"
#include "sender.h"
#include "thread_canceller.h"

int main(int argc, char* argv[]) {

    if(argc != 4) {
        printf("Wrong number of arguments! 3 arguments required, %d provided.", argc - 1);
        return 0;
    }

    unsigned short LOCAL_PORT = atoi(argv[1]);
    char* REMOTE_IP = argv[2];
    unsigned short REMOTE_PORT = atoi(argv[3]);

    printf("ATTEMPTING TO RUN ON LOCAL PORT: %d \n", LOCAL_PORT);
    printf("CONNECTING TO %s:%d \n", REMOTE_IP, REMOTE_PORT);

    // set up mutexes and any concurrency related stuff

    pthread_mutex_t receivedMessagesSemaphore = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t messagesToBeSentSemaphore = PTHREAD_MUTEX_INITIALIZER;

    // set up 2 Linked Lists
    List* receivedMessages = List_create();
    List* messagesToBeSent = List_create();



    pthread_t* keyboard_thread = keyboard_init(messagesToBeSent, &messagesToBeSentSemaphore);
    pthread_t* sender_thread = sender_init(REMOTE_PORT, REMOTE_IP, messagesToBeSent, &messagesToBeSentSemaphore);

    pthread_t* screen_thread = screen_init(receivedMessages, &receivedMessagesSemaphore);

    pthread_t* receiver_thread = receiver_init(LOCAL_PORT, receivedMessages, &receivedMessagesSemaphore);

    thread_canceller_init(keyboard_thread,
                          sender_thread,
                          screen_thread,
                          receiver_thread,
                          &receivedMessagesSemaphore,
                          &messagesToBeSentSemaphore,
                          receivedMessages,
                          messagesToBeSent);

    pthread_join(*receiver_thread, NULL);
    pthread_join(*screen_thread, NULL);
    pthread_join(*keyboard_thread, NULL);
    pthread_join(*sender_thread, NULL);
    return 0;
}

