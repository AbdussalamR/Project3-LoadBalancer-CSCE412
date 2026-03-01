#include "Switch.h"
#include <iostream>

#define BLUE   "\033[34m"
#define RED    "\033[31m"
#define GREEN   "\033[32m"
#define RESET  "\033[0m"

/**
 * @brief Initializes two LoadBalancers for different job types.
 */
Switch::Switch(int startServers) : p_count(0), s_count(0) {
    LB_Processing = new LoadBalancer(startServers/2);
    LB_Streaming = new LoadBalancer(startServers/2);
}

/**
 * @brief Cleans up allocated LoadBalancers.
 */
Switch::~Switch() {
    delete LB_Processing;
    delete LB_Streaming;
}

/**
 * @brief Routes a request based on job type.
 *
 * 'P' → Processing LoadBalancer
 * 'S' → Streaming LoadBalancer
 */
void Switch::routeRequest(Request r) {
    if (r.job_type == 'P') {
        LB_Processing->addRequest(r);
        p_count++;
    } else {
        LB_Streaming->addRequest(r);
        s_count++;
    }
}

/**
 * @brief Advances both LoadBalancers by one clock cycle.
 *
 * Each LoadBalancer:
 * - Processes requests
 * - Dynamically adjusts server count
 */
void Switch::step() {
    LB_Processing->req_to_idle_server();
    LB_Streaming->req_to_idle_server();

    LB_Processing->dynamic_allocation();
    LB_Streaming->dynamic_allocation();
}

/**
 * @brief Displays summary of routed jobs and final queue sizes.
 */
void Switch::Summary() {
    std::string report = "\n========================================\n"
                         "         FINAL SIMULATION REPORT    \n"
                         "========================================\n";

    report += "Starting Queue Size: " + std::to_string(LB_Processing->numStart + LB_Streaming->numStart) + "\n";
    report += "Ending Queue Size:   " + std::to_string(LB_Processing->requestQueue.size() + LB_Streaming->requestQueue.size()) + "\n";
    report += "Task Time Range:     5 to 55 clock cycles\n\n";

    report += "--- Processing (P) Cluster ---\n";
    report += "Jobs Routed:         " + std::to_string(p_count) + "\n";
    report += "Final Server Count:  " + std::to_string(LB_Processing->servers.size()) + "\n\n";

    report += "--- Streaming (S) Cluster ---\n";
    report += "Jobs Routed:         " + std::to_string(s_count) + "\n";
    report += "Final Server Count:  " + std::to_string(LB_Streaming->servers.size()) + "\n\n";

    int totalBlocked = LB_Processing->blockedCount + LB_Streaming->blockedCount;
    report += "--- Security Status ---\n";
    report += "Total Blocked IPs:   " + std::to_string(totalBlocked) + "\n";
    report += "========================================\n";

    std::cout << BLUE << report << RESET << std::endl;


    LB_Processing->log(report);
}