#ifndef CODE_UTILS_H
#define CODE_UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <set>
#include <chrono>
#include <iterator>
#include <algorithm>

#define MIN_LETTERS       3
#define MAX_LETTERS       15

struct TimeIt {
    std::string message;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    std::chrono::microseconds duration{};

    explicit TimeIt(std::string message) : message(std::move(message)) {
        start = std::chrono::high_resolution_clock::now();
    }
    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start);

        std::cout << "\t------------\n" << "\tTime taken to " <<  message
        << " : " << (duration.count()) << "μs\n" << "\t------------\n";
    }
};

bool compare3rdLetter(std::string &first, std::string &second);

bool compare3rdLetterOnwards(std::string &first, std::string &second);

void vectorToFile(std::vector<std::string> &vector, std::ofstream &file);

std::vector<std::string> TaskFilter(std::ifstream &readFile);

#endif // CODE_UTILS_H