#include "list.h"
#include <pthread.h>
#include "thread_canceller.h"

#ifndef ASSIGNMENT2_RECEIVER_H
#define ASSIGNMENT2_RECEIVER_H

// Starts a thread responsible for receiving messages on the LOCAL_PORT
pthread_t* receiver_init(unsigned short LOCAL_PORT, List* receivedMessages, pthread_mutex_t* semaphorePtr);
void receiver_shutdown();

#endif //ASSIGNMENT2_RECEIVER_H
