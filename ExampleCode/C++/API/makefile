CC		= g++
CFLAGS = -O0 -g -Wall -Wextra -pedantic-errors  -w -std=c++11

all:
	$(CC) $(CFLAGS) POST_key.cpp API.cpp -o key.out -lcurl
	$(CC) $(CFLAGS) POST_key_append.cpp API.cpp -o append_key.out -lcurl
	$(CC) $(CFLAGS) POST_email.cpp API.cpp -o email.out -lcurl
	$(CC) $(CFLAGS) POST_email_append.cpp API.cpp -o append_email.out -lcurl
	$(CC) $(CFLAGS) POST_API_Test.cpp API.cpp -o api.out -lcurl
	$(CC) $(CFLAGS) tests.cpp API.cpp -o tests.out -lcurl
	$(CC) $(CFLAGS) GET_search.cpp API.cpp -o search.out -lcurl

clean:
	rm key.out
	rm append_key.out
	rm email.out
	rm append_email.out
	rm api.out
	rm tests.out
	rm search.out
