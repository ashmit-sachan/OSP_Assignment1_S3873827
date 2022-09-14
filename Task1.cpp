#include "Utils.h"

int main(int argc, char** argv) {

    std::ifstream readFile(argv[1]);
    std::ofstream writeFile (argv[2]);

    std::vector<std::string> filteredData = TaskFilter(readFile);

    std::cout << "Start: Writing filtered words to file" << "\n";
    TimeIt write = TimeIt("write filtered words to file");
    for(auto& str: filteredData)
        writeFile << str << "\n";
    write.stop();
    std::cout << "End: Writing filtered words to file" << "\n";

    readFile.close();
    writeFile.close();
}
