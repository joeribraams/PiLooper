CC = g++
CFLAGS = -I/usr/local/include -Wall -std=c++17 -lwiringPi
LDFLAGS= -ljack

all: example

example : jack_module.o looper.o main.o
	$(CC) -o $@ $(CFLAGS) jack_module.o looper.o main.o $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f example
