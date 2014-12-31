CC		= g++
CFLAGS = -O0 -g -Wall -Wextra -pedantic-errors  -w -std=c++11

all:
	$(CC) $(CFLAGS) POST_simple.cpp -o simple.out -lcurl
	$(CC) $(CFLAGS) POST_isense.cpp api.cpp -o post.out  -lcurl
	$(CC) $(CFLAGS) POST_API_Test.cpp api.cpp -o api.out  -lcurl
