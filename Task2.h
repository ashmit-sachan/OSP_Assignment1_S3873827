#ifndef CODE_TASK2_H
#define CODE_TASK2_H

#include <sys/stat.h>
#include "sys/wait.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "Utils.h"


std::vector<std::ofstream*> files;

std::vector<std::vector<std::string>*> words;

pid_t children[MAX_LETTERS - MIN_LETTERS + 1];

/*
 * @param
 * @return
 */
void map2(std::ifstream &readFile);

/*
 * @param
 * @return
 */
void reduce2(std::ofstream &writeFile);


#endif // CODE_TASK2_H