#include "Task2.h"


int main(int argc, char** argv) {

    std::ifstream readFile(argv[1]);
    std::ofstream writeFile (argv[2]);

    std::cout << "Start: Task 2" << "\n";
    TimeIt task = TimeIt("Task 2");
    map2(readFile);
    reduce2(writeFile);
    task.stop();
    std::cout << "End: Task 2" << std::endl;

    readFile.close();
    writeFile.close();

    return EXIT_SUCCESS;
}


void map2(std::ifstream &readFile) {
    std::vector<std::string> word_s = TaskFilter(readFile);

    for (int i = MIN_LETTERS; i <= MAX_LETTERS; ++i) {
        files.push_back(new std::ofstream("./words/words" + std::to_string(i) + ".txt"));
        words.push_back(new std::vector<std::string>);
    }

    std::cout << "Start: Separating words of different lengths" << "\n";
    TimeIt separator = TimeIt("separate words of different lengths");
    for(const auto& word : word_s)
        (words[word.size() - MIN_LETTERS])->push_back(word);
    separator.stop();
    std::cout << "End: Separating words of different lengths" << "\n";

    std::cout << "Start: Parent fork " << "( PID: " << getpid() << " )" << std::endl;
    TimeIt p_fork = TimeIt(std::string("complete Fork( PID: " + std::to_string(getpid()) + "  [PPID: " + std::to_string(getppid()) + "] )"));
    for (int i=0; i <= MAX_LETTERS - MIN_LETTERS; ++i) {
        children[i] = fork();
        if (children[i] == 0) {
            std::cout << "Start: Fork to sort and write words of length " << i + MIN_LETTERS << "( PID: " << getpid() << "  [PPID: " << getppid() << "] )" << std::endl;
            TimeIt fork = TimeIt(std::string("complete Fork( PID: " + std::to_string(getpid()) + "  [PPID: " + std::to_string(getppid()) + "] )"));

            std::sort(words[i]->begin(),words[i]->end(), compare3rdLetterOnwards);

            vectorToFile(*words[i], *files[i]);

            files[i]->close();

            fork.stop();
            std::cout << "End: Fork to sort and write words of length " << i + MIN_LETTERS << "( PID: " << getpid() << "  [PPID: " << getppid() << "] )" << std::endl;

            kill(getpid(), SIGKILL);
        }
    }

    for(auto &child : children)
        if (child > 0)
            wait(nullptr);

    p_fork.stop();
    std::cout << "End: Parent fork " << "( PID: " << getpid() << " )" << std::endl;
}


void reduce2(std::ofstream &writeFile) {
    std::vector<std::ifstream> sorted_files;
    std::vector<std::string> read_words;


    std::cout << "Start: Reduce" << "\n";
    TimeIt reduce = TimeIt("reduce");
    for (int i = MIN_LETTERS; i <= MAX_LETTERS; ++i) {
        sorted_files.emplace_back("./words/words" + std::to_string(i) + ".txt");
        std::string temp;

        if (getline(sorted_files[i - MIN_LETTERS], temp)) {
            read_words.push_back(temp);
        }
    }

    int numTrue = static_cast<int>(read_words.size());

    while(numTrue > 0) {
        std::sort(read_words.begin(), read_words.end(),
                  [&](std::string &i,std::string &j){
                            return compare3rdLetterOnwards(i, j);
                        }
                  );

        writeFile << read_words[0] << "\n";

        if (!getline(sorted_files[read_words[0].size() - MIN_LETTERS], read_words[0])) {
            for (int i = 0; i < numTrue; ++i)
                read_words[i] = read_words[i + 1];

            read_words.pop_back();

            numTrue =  static_cast<int>(read_words.size());
        }
    }
    reduce.stop();
    std::cout << "End: Reduce" << "\n" << std::endl;
}
