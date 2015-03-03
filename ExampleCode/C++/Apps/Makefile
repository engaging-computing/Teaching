# Makefile for the iSENSE projects involving C++
# Designed to quickly compile the C++ code (only if files are changed)
CC = g++

# NOTES: -lcurl is required. -std=c++0x is also needed for to_string.
CFLAGS = -Wall -Werror -pedantic -std=c++0x -lcurl


# Makes all of the C++ projects, appends a ".out" for easy removal in make clean
all:	baseball_app.out dice_app.out

baseball_app.out:	baseball_app.o API.o
	$(CC) baseball_app.o API.o -o baseball_app.out $(CFLAGS)

baseball_app.o:	baseball_app.cpp
	$(CC) -c baseball_app.cpp $(CFLAGS)

dice_app.out:	dice_app.o API.o
	$(CC) dice_app.o API.o -o dice_app.out $(CFLAGS)

dice_app.o:	dice_app.cpp
	$(CC) -c dice_app.cpp $(CFLAGS)

API.o:	API.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c API.cpp $(CFLAGS)

clean:
	rm *.o
	rm *.out
