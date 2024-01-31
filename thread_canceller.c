//
// Created by ilyan on 10/26/2023.
//

#include <stdio.h>
#include "thread_canceller.h"

static pthread_t* static_keyboard_thread;
static pthread_t* static_sender_thread;
static pthread_t* static_screen_thread;
static pthread_t* static_receiver_thread;
static pthread_mutex_t* static_receivedMessagesMutexPtr;
static pthread_mutex_t* static_messagesToBeSentMutexPtr;
static List* static_receivedMessages;
static List* static_messagesToBeSent;

void thread_canceller_init(
        pthread_t* keyboard_thread,
        pthread_t* sender_thread,
        pthread_t* screen_thread,
        pthread_t* receiver_thread,
        pthread_mutex_t* receivedMessagesMutexPtr,
        pthread_mutex_t* messagesToBeSentMutexPtr,
        List* receivedMessages,
        List* messagesToBeSent) {

    static_keyboard_thread = keyboard_thread;
    static_sender_thread = sender_thread;
    static_screen_thread = screen_thread;
    static_receiver_thread = receiver_thread;
    static_receivedMessagesMutexPtr = receivedMessagesMutexPtr;
    static_messagesToBeSentMutexPtr = messagesToBeSentMutexPtr;
    static_receivedMessages = receivedMessages;
    static_messagesToBeSent = messagesToBeSent;

}

void cancel_threads(bool isFromSenderThread) {

    pthread_cancel(*static_keyboard_thread);
    pthread_cancel(*static_screen_thread);

    if(isFromSenderThread) {
        pthread_cancel(*static_receiver_thread);

    } else {
        pthread_cancel(*static_sender_thread);

    }

    exit(0);
}