#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <cstdlib>
#include <sstream>

/**
 * @struct Request
 * @brief Represents a web request handled by the load balancer.
 *
 * A Request contains:
 * - Incoming IP address
 * - Outgoing IP address
 * - Processing time (in clock cycles)
 * - Job type ('P' for Processing, 'S' for Streaming)
 */
struct Request {
    std::string ip_in;     ///< Incoming IP address
    std::string ip_out;    ///< Outgoing IP address
    int time;              ///< Processing time in clock cycles
    char job_type;         ///< 'P' for Processing, 'S' for Streaming

    /**
     * @brief Default constructor.
     *
     * Generates a randomized request including:
     * - Random IP addresses
     * - Random processing time (5–55 clock cycles)
     * - Random job type
     */
    Request() {
        ip_in = generateIP();
        ip_out = generateIP();
        time = rand() % 50 + 5;

        if (rand() % 2 == 0)
            job_type = 'P';
        else
            job_type = 'S';
    }

private:
    /**
     * @brief Generates a random IPv4 address.
     * @return A string representing an IP address in dotted format.
     */
    std::string generateIP() {
        std::stringstream ss;
        for (int i = 0; i < 4; ++i) {
            ss << rand() % 256;
            if (i < 3)
                ss << ".";
        }
        return ss.str();
    }
};

#endif
