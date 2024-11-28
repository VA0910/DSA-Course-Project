all: main.o 
	g++ main.o 

main.o: main.cpp Graph.h PriorityQueue.h
	g++ -c main.cpp Graph.h PriorityQueue.h


clean:
	rm -f *.o main
