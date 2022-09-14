#include "Utils.h"

bool compare3rdLetter(std::string &first, std::string &second) {
    return first[2] < second[2];
}


bool compare3rdLetterOnwards(std::string &first, std::string &second) {
    std::string t_first = first;
    std::string t_second = second;
    t_first.erase(0,2);
    t_second.erase(0,2);

    return (t_first < t_second);
}


void vectorToFile(std::vector<std::string> &vector, std::ofstream &file) {
    for(const std::string& item : vector)
        file << item << "\n";
}

std::vector<std::string> TaskFilter(std::ifstream &readFile)
{
    std::string text;
    std::set<std::string> clean_file;

    std::cout << "Filtering Started" << "\n";
    TimeIt filter = TimeIt("filter dirty data");

    while (getline (readFile, text)) {
        for(int i=0; i < static_cast<int>(text.size()); i++)
            if (!isalpha(text[i]))
                text.erase(i--, 1);

        if(text.size() >= 3 && text.size() <= 15)
            clean_file.insert(text);
    }

    filter.stop();
    std::cout << "Filtering Done" << "\n";

    std::vector<std::string> vec = std::vector<std::string> (clean_file.begin(), clean_file.end());

    std::cout << "Shuffling Started" << "\n";
    TimeIt shuffling = TimeIt("shuffle dirty data");

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(vec), std::end(vec), rng);

    shuffling.stop();
    std::cout << "Shuffling Done" << "\n";


    return vec;
}
