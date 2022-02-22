CC = g++
CFLAGS = -g -Wall -std=c++11

a.out: main_lab6.cc
	$(CC) $(CFLAGS) main_lab6.cc -o a.out

clean:
	rm -rf *.o a.out
