#ifndef CODE_TASK3_H
#define CODE_TASK3_H

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

//std::vector<std::vector<std::string>*> words;

std::vector<std::vector<int>*> indexes;


void* map3(void *varg);

void* reduce3(void *varg);

void* writeFifo(void* arguments);


#endif //CODE_TASK3_H
