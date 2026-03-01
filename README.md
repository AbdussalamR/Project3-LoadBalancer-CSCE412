# CSCE 412 – Project 3: Load Balancer Simulation

## Overview

This project simulates a large-scale web request load balancing system.  
The system generates randomized web requests and distributes them across multiple web servers while dynamically scaling server capacity to maintain efficiency.

The simulation models:

- Request generation
- Web server processing
- Load balancing
- Dynamic server allocation
- Firewall IP range blocking
- Logging and system statistics

---

## System Architecture

The system consists of the following components:

### 1. Request
Represents a web request containing:
- Incoming IP address
- Outgoing IP address
- Processing time (clock cycles)
- Job type ('P' = Processing, 'S' = Streaming)

### 2. WebServer
Simulates a single server that:
- Processes one request at a time
- Tracks remaining processing time
- Becomes available after completion

### 3. LoadBalancer
Responsible for:
- Managing request queue
- Assigning requests to idle servers
- Blocking IP ranges (firewall)
- Dynamically adding/removing servers
- Maintaining system time
- Logging events

### 4. Switch (Bonus)
Routes jobs based on job type:
- Streaming jobs → streaming load balancer
- Processing jobs → processing load balancer

---

## Dynamic Scaling Policy

To prevent overload or underutilization:

- If queue size > 80 × number_of_servers → add 1 server
- If queue size < 50 × number_of_servers → remove 1 server (if idle)

This keeps the queue within an optimal operating range.

---

## Firewall Mechanism

The load balancer includes an IP range blocker.

Requests originating from blocked IP ranges(beginning with 2) are denied and logged.

## Logging

All events are written to:

```bash
log.txt
```

Logged events include:
- Request assignments
- Scaling events
- Firewall blocks
- System initialization

---

## Build Instructions

### Using Make
First run: 
```bash
make clean
```
To clean build files
Then:
```bash
make
```
Then:
```bash
./loadbalancer
```

The program will prompt for:
- Number of starting servers
- Total simulation time(clock cycles)

