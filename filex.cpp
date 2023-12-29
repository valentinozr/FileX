#include <iostream>
#include <filesystem>
#include <cstdlib> // For system function

namespace fs = std::filesystem;

void listFiles(const std::string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << entry.path().filename() << std::endl;
    }
}

void openFile(const std::string& filename) {
    std::string command;

    #ifdef _WIN32
        command = "start " + filename;
    #elif __APPLE__
        command = "open " + filename;
    #else
        command = "xdg-open " + filename;
    #endif

    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Error: Failed to open file." << std::endl;
    }
}

std::string getUserInput() {
    std::string userInput;
    std::cout << "\nEnter a directory or file name to explore/open, 'Q' to quit, or '..' to go up: ";
    std::getline(std::cin, userInput);
    return userInput;
}

int main() {
    std::cout << "--------------------------\n";
    std::cout << "FileX Basic File Explorer\n";
    std::cout << "-------------------------\n";
    std::cout << "Made By ValentinOZR\n";
    std::cout << "-------------------\n";

    std::string currentPath = ".";

    while (true) {
        system("clear"); // Clear screen for a cleaner display
        std::cout << "\nCurrent directory: " << currentPath << std::endl;
        std::cout << "Files in the current directory:\n";
        listFiles(currentPath);

        std::string userInput = getUserInput();

        if (userInput == "Q") {
            break;
        } else if (userInput == "..") {
            currentPath = fs::canonical(currentPath + "/..").string();
        } else {
            fs::path newPath = fs::canonical(fs::path(currentPath) / userInput);

            if (fs::is_directory(newPath)) {
                currentPath = newPath.string();
            } else {
                openFile(newPath.string());
            }
        }
    }

    return 0;
}
