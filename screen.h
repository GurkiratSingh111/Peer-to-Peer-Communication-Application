#include "list.h"
#include <pthread.h>

#ifndef ASSIGNMENT2_SCREEN_H
#define ASSIGNMENT2_SCREEN_H

pthread_t* screen_init(List* receivedMessages, pthread_mutex_t* semaphorePtr);

#endif //ASSIGNMENT2_SCREEN_H
