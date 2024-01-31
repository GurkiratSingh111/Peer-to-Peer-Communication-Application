#include "keyboard.h"

#define MAX_MESSAGE_LEN 256

static List* messages;
static pthread_mutex_t* semaphorePointer;
static pthread_t keyboardThread;

int terminate_process = 0;

void start_keyboard_thread();
void* keyboard_take_input_procedure(void* args);

pthread_t* keyboard_init(List* messagesToBeSent, pthread_mutex_t* semaphorePtr) {
    messages = messagesToBeSent;
    semaphorePointer = semaphorePtr;
    start_keyboard_thread();
    return &keyboardThread;
}

void start_keyboard_thread() {
    int pthread_creation_status = pthread_create(
            &keyboardThread,
            NULL,
            keyboard_take_input_procedure,
            NULL
            );
    if(pthread_creation_status != 0) {
        printf("An error has occurred in keyboard.start_keyboard_thread() while creating a thread.");
        return;
    }

}

void* keyboard_take_input_procedure(void* args) {
    while(1) {
        char* messageToBeSent = (char*) (malloc(MAX_MESSAGE_LEN * sizeof(char)));
        // get user input
//        scanf("%s", messageToBeSent);
        fgets( messageToBeSent, MAX_MESSAGE_LEN, stdin);
        int messageLength = strlen(messageToBeSent);

        if( (messageLength > 0) && (messageToBeSent[messageLength - 1] == '\n'))
            messageToBeSent[messageLength - 1] = '\0';

        pthread_mutex_lock(semaphorePointer);
        {
            List_prepend(messages, messageToBeSent);
        }
//        printf("Message you wanna send is: %s\n", messageToBeSent);
        pthread_mutex_unlock(semaphorePointer);
    }

}