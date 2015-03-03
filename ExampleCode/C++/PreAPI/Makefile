CC = g++
CFLAGS = -O0 -g -Wall -Wextra -pedantic-errors  -w

all:
	$(CC) $(CFLAGS) GET_curl.cpp -o get.out -lcurl
	$(CC) $(CFLAGS) POST_simple.cpp -o simple.out -lcurl

clean:
	rm get.out
	rm simple.out
