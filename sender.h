#include "list.h"
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "thread_canceller.h"

#ifndef ASSIGNMENT2_SENDER_H
#define ASSIGNMENT2_SENDER_H

pthread_t* sender_init(unsigned short REMOTE_PORT, char* REMOTE_IP, List* messagesToBeSent, pthread_mutex_t* semaphorePtr);

#endif //ASSIGNMENT2_SENDER_H
