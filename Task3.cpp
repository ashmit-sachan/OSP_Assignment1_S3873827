#include "Task3.h"

int main(int argc, char** argv) {
    std::ifstream readFile(argv[1]);
    std::ofstream writeFile (argv[2]);
    Global = TaskFilter(readFile);

    std::cout << "Start: Task 3" << "\n";
    TimeIt task = TimeIt("Task 3");
    pthread_t map_thread, reduce_thread;

    pthread_mutex_init(&lock, nullptr);

    pthread_create(&map_thread, nullptr, &map3, nullptr);
    pthread_create(&reduce_thread, nullptr, &reduce3, &writeFile);

    pthread_join(map_thread,nullptr);
    pthread_join(reduce_thread, nullptr);

    pthread_mutex_destroy(&lock);
    task.stop();
    std::cout << "End: Task 3" << std::endl;

    return EXIT_SUCCESS;
}


void* map3(void *arg) {
    pthread_mutex_lock(&lock);
    int index=0;

    for (int i = MIN_LETTERS; i <= MAX_LETTERS; ++i)
        indexes.push_back(new std::vector<int>);

    std::cout << "Start: Separating indexes of different word lengths in Global array" << "\n";
    TimeIt separator = TimeIt("separate words of different lengths");
    for(auto &word: Global) {
        indexes[word.size() - MIN_LETTERS]->push_back(index);
        ++index;
    }
    separator.stop();
    std::cout << "End: Separating indexes of different word lengths in Global array" << "\n";

    pthread_t threads[MAX_LETTERS - MIN_LETTERS + 1];

    for (int i = 0; i < MAX_LETTERS - MIN_LETTERS + 1; ++i) {
        pthread_create(&threads[i], nullptr, &writeFifo, indexes[i]);
    }

    for (unsigned long &thread : threads)
        pthread_join(thread, nullptr);

    pthread_mutex_unlock(&lock);

    return nullptr;
}


void* writeFifo(void* arg) {
    auto index_s = *static_cast<std::vector<int> *>(arg);
    int size = static_cast<int>(Global[index_s.at(0)].size());

    std::cout << "Start: Sort and write FIFO" << size << std::endl;
    TimeIt thread = TimeIt(std::string("sort and write FIFO" + std::to_string(size)));
    std::sort(index_s.begin(), index_s.end(),
               [&](int &i,int &j){
                    return compare3rdLetterOnwards(Global[i], Global[j]);
                }
    );

    std::string fifo_name = "fifo/FIFO" + std::to_string(size);
    if (mkfifo(fifo_name.c_str(), 0777) != 0) {
        std::ofstream fifo(fifo_name);

        for(auto &index : index_s) {
            fifo << std::to_string(index) << "\n";
        }
    }

    thread.stop();
    std::cout << "End: Sort and write FIFO" << size << std::endl;

    pthread_exit(nullptr);
}

void* reduce3(void *arg) {
    auto writeFile = static_cast<std::ofstream *>(arg);

    std::vector<std::ifstream> sorted_files;
    std::vector<int> read_words;
    std::string temp;


    std::cout << "Start: Reduce" << "\n";
    TimeIt reduce = TimeIt("reduce");
    for (int i = MIN_LETTERS; i <= MAX_LETTERS; ++i) {
        sorted_files.emplace_back("./fifo/FIFO" + std::to_string(i));

        if (getline(sorted_files[i - MIN_LETTERS], temp))
            read_words.push_back(std::stoi(temp));
    }

    int numTrue = static_cast<int>(read_words.size());

    while(numTrue > 0) {
        std::sort(read_words.begin(), read_words.end(),
                  [&](int &i,int &j){
                      return compare3rdLetterOnwards(Global[i], Global[j]);
                  });

        *writeFile << Global[read_words[0]] << "\n";


        if (!getline(sorted_files[Global[read_words[0]].size() - MIN_LETTERS], temp)) {

            for (int i = 0; i < numTrue; ++i)
                read_words[i] = read_words[i + 1];

            read_words.pop_back();

            numTrue =  static_cast<int>(read_words.size());
        } else {
            read_words[0] = std::stoi(temp);
        }
    }
    reduce.stop();
    std::cout << "End: Reduce" << "\n" << std::endl;

    pthread_exit(nullptr);
}
