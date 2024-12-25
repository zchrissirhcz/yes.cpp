#include <iostream>  
#include <csignal>  
#include <atomic>  
#include <thread>  
#include <cstdlib>  

// Global variables  
std::atomic<bool> pauseFlag(false);  
int logLevel = 1; // 1: Info, 2: Warning, 3: Error  

// Signal handler function
void signalHandler(int signum) {  
    if (signum == SIGINT) {  
        pauseFlag.store(true);  
        std::cout << "\nReceived SIGINT signal, entering debug mode.\n";  
    }  
}  

// User interaction function
void interactiveSession() {  
    while (true) {  
        std::cout << "\n--- Debug Menu ---\n"
                  << "1. View log level\n"
                  << "2. Change log level\n"
                  << "3. Continue running\n"
                  << "4. Exit program\n"
                  << "Enter your choice: ";  

        int choice;  
        if (std::cin >> choice) {  
            switch (choice) {  
                case 1:  
                    std::cout << "Current log level: " << logLevel << "\n";  
                    break;
                case 2: {
                    std::cout << "Enter new log level (1: Info, 2: Warning, 3: Error): ";  
                    int newLevel;  
                    if (std::cin >> newLevel && newLevel >= 1 && newLevel <= 3) {
                        logLevel = newLevel;
                        std::cout << "Log level updated to: " << logLevel << "\n";
                    } else {
                        std::cout << "Invalid log level.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    break;
                }
                case 3:  
                    std::cout << "Continuing program execution.\n";  
                    return;
                case 4:  
                    std::cout << "Terminating program.\n";  
                    std::exit(0);
                default:  
                    std::cout << "Invalid choice, please try again.\n";  
            }  
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number.\n";
        }
    }  
}  

int main() {  
    std::signal(SIGINT, signalHandler);  

    while (true) {  
        if (logLevel >=1) std::cout << "[INFO] Program is running...\n";  
        if (logLevel >=2) std::cout << "[WARNING] This is a warning message.\n";  
        if (logLevel >=3) std::cout << "[ERROR] This is an error message.\n";  
        
        std::this_thread::sleep_for(std::chrono::seconds(2));  

        if (pauseFlag.load()) {  
            pauseFlag.store(false);
            interactiveSession();
        }  
    }  
    return 0;  
}