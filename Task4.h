#ifndef CODE_TASK4_H
#define CODE_TASK4_H

#include "Utils.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <sys/stat.h>
#include <algorithm>
#include <thread>
#include <pthread.h>
#include <fcntl.h>


std::vector<std::string> Global;

pthread_mutex_t lock;

std::vector<std::vector<int>*> indexes;


void* map4(void *varg);

void* reduce4(void *varg);

void* writeFifo(void* arguments);



#endif //CODE_TASK4_H
