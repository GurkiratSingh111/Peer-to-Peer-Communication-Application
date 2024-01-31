//
// Created by ilyan on 10/26/2023.
//

#include <stdlib.h>

#include <pthread.h>
#include "list.h"

#ifndef ASSIGNMENT2_THREAD_CANCELLER_H
#define ASSIGNMENT2_THREAD_CANCELLER_H

void thread_canceller_init(
        pthread_t* keyboard_thread,
        pthread_t* sender_thread,
        pthread_t* screen_thread,
        pthread_t* receiver_thread,
        pthread_mutex_t* receivedMessagesMutexPtr,
        pthread_mutex_t* messagesToBeSentMutexPtr,
        List* receivedMessages,
        List* messagesToBeSent);

void cancel_threads(bool isFromSenderThread);

#endif //ASSIGNMENT2_THREAD_CANCELLER_H
