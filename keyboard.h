#include "receiver.h"
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#ifndef ASSIGNMENT2_KEYBOARD_H
#define ASSIGNMENT2_KEYBOARD_H

pthread_t* keyboard_init(List* messagesToBeSent, pthread_mutex_t* semaphorePtr);

#endif //ASSIGNMENT2_KEYBOARD_H
