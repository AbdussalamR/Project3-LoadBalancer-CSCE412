#ifndef SWITCH_H
#define SWITCH_H

#include "LoadBalancer.h"

/**
 * @class Switch
 * @brief Higher-level load balancer that routes requests
 *        to separate LoadBalancers based on job type.
 *
 * The Switch:
 * - Routes Processing jobs ('P') to one LoadBalancer
 * - Routes Streaming jobs ('S') to another LoadBalancer
 * - Advances both systems simultaneously
 * - Maintains routing statistics
 */
class Switch {
public:
    LoadBalancer* LB_Processing;              ///< LoadBalancer for processing jobs
    LoadBalancer* LB_Streaming;               ///< LoadBalancer for streaming jobs

    int p_count;                     ///< Count of processing jobs routed
    int s_count;                     ///< Count of streaming jobs routed
 
    /**
     * @brief Constructs a Switch and splits servers between two LoadBalancers.
     * @param startServers Total number of servers to divide.
     */
    Switch(int startServers);

    /**
     * @brief Destructor. Cleans up dynamically allocated LoadBalancers.
     */
    ~Switch();

    /**
     * @brief Routes a request to the appropriate LoadBalancer.
     * @param r The request to route.
     */
    void routeRequest(Request r);

    /**
     * @brief Advances both LoadBalancers by one clock cycle.
     */
    void step();

    /**
     * @brief Displays summary statistics for both systems.
     */
    void Summary();
};

#endif