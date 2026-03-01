#include <iostream>
#include <ctime>
#include <vector>
#include "Switch.h"

// ANSI color codes for terminal formatting
#define GOLD    "\033[33m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"



/*
 * main()
 *
 * Driver program for Load Balancer / Switch simulation.
 *
 * Responsibilities:
 *  - Collect user input (server count and simulation runtime)
 *  - Generate initial request queue (servers * 100)
 *  - Run simulation loop for specified clock cycles
 *  - Randomly inject new requests during runtime
 *  - Periodically display queue sizes
 *  - Output final summary statistics
 */
int main() {
    srand(time(0));

    int numServers{};
    int runTime{};
    int arrivalRate{10};


    std::cout << GOLD << "========================================" << RESET << std::endl;
    std::cout << GOLD << "            LOAD BALANCER v3.0          " << RESET << std::endl;
    std::cout << GOLD << "========================================" << RESET << std::endl;

    std::cout << "Enter the number of servers to start with: ";
    std::cin >> numServers;
    std::cout << "Enter the total simulation time (in clock cycles): ";
    std::cin >> runTime;

    if (numServers <= 0 || runTime <= 0) {
        std::cout << RED << "Invalid input. Values must be positive integers." 
                  << RESET << std::endl;
        return 1;
    }
    
    Switch arSwitch(numServers);

    int initialQueueSize = numServers * 100;
    std::cout << "Generating initial queue of " << initialQueueSize << " requests..." << std::endl;
    for (int i = 0; i < initialQueueSize; i++) {
        arSwitch.routeRequest(Request());
    }

    std::cout << GREEN << "Starting simulation for " << runTime << " clock cycles..." << RESET << std::endl;

    for (int t = 0; t < runTime; t++) {
        if (rand() % arrivalRate == 0) {
            arSwitch.routeRequest(Request());
        }
        arSwitch.step();

        if (t % 100 == 0) {
            std::cout << "Time: " << t << " cycles - Processing Queue: " 
                      << arSwitch.LB_Processing->requestQueue.size() 
                      << ", Streaming Queue: " 
                      << arSwitch.LB_Streaming->requestQueue.size() 
                      << std::endl;
        }
    }

    std::cout << RED << "Simulation complete!" << RESET << std::endl;
    std::cout << "Starting Queue Size: " << initialQueueSize << std::endl;

    arSwitch.Summary();

    return 0;
}