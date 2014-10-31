CC		= g++
CFLAGS = -O0 -g -Wall -Wextra -pedantic-errors  -w

all:
	$(CC) $(CFLAGS) POST_curl.cpp -o post.out -lcurl
	#$(CC)   -o post_parson.out POST_curl_parson.cpp parson.c -lcurl

post:
	$(CC) -Wall -g POST_curl.cpp -o post.out -lcurl

post_jans:
	$(CC) -Wall -g POST_curl_parson.cpp parson.c -o post_parson.out -lcurl
