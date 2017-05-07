CXX=gcc
OBJS=heapsort.o
NAME=heapsort.c

algo: $(OBJS)
	$(CXX) -Wall -lrt -g  $(OBJS) -o algo

heapsort.o: heapsort.c
	$(CXX) -Wall -lrt -g -c heapsort.c -o heapsort.o

clean:
	rm -f *.o algo
