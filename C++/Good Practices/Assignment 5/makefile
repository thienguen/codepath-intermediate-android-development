# Make file for assignment #5, Virtual Fish Tank

CC	= g++ 
CCFLAGS = -Wall -Wextra -pedantic -std=c++11 -g

OBJS	= main.o Tank.o Fish.o
DEPS	= Tank.h Fish.h

all: main

main: $(OBJS)
	@echo "Compiling Virtual Aquarium..."
	$(CC) $(CCFLAGS) -o virt_aqua $(OBJS)
	@echo "Done! Run virt_aqua"

main.o:	main.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c main.cpp

Tank.o:	Tank.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c Tank.cpp

Fish.o:	Fish.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c Fish.cpp
	
