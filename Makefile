CC = g++
CFLAGS = -Wall -Werror -std=c++11

# The name of your final executable
TARGET = loadbalancer

# List of object files needed
OBJS = main.o WebServer.o LoadBalancer.o Switch.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Request.h WebServer.h LoadBalancer.h Switch.h
	$(CC) $(CFLAGS) -c main.cpp

WebServer.o: WebServer.cpp WebServer.h Request.h
	$(CC) $(CFLAGS) -c WebServer.cpp

LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h WebServer.h Request.h
	$(CC) $(CFLAGS) -c LoadBalancer.cpp

Switch.o: Switch.cpp Switch.h LoadBalancer.h
	$(CC) $(CFLAGS) -c Switch.cpp

# Clean up generated files
clean:
	rm -f *.o $(TARGET) log.txt