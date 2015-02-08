# Makefile for the iSENSE projects involving C++
# Designed to quickly compile the C++ code
CC = g++

# NOTES: -lcurl is required. std=c++11 is also needed for to_string
CFLAGS = -O0 -g -Wall -Werror -Wextra -pedantic-errors -w -std=c++11 -lcurl

# Makes all projects that have changed
all:	key key_byID key_byName email email_byID email_byName

# 	$(CC) $(CFLAGS) GET_search.cpp API.cpp -o search.out -lcurl
# 	$(CC) $(CFLAGS) GET_Datasets.cpp API.cpp -o datasets.out -lcurl
# 	$(CC) $(CFLAGS) tests.cpp API.cpp -o tests.out -lcurl
#	$(CC) $(CFLAGS) POST_API_Test.cpp API.cpp -o api.out -lcurl

# Contributor key test
key:	POST_key.o API.o
	$(CC) POST_key.o API.o -o key.out $(CFLAGS)

API.o:
	$(CC) -c API.cpp $(CFLAGS)

POST_key.o:
	$(CC) -c POST_key.cpp $(CFLAGS)

# Appending by dataset ID test
key_byID:	POST_key_append_byID.o
	$(CC) POST_key_append_byID.o API.o -o append_key_byID.out $(CFLAGS)

POST_key_append_byID.o:
	$(CC) -c POST_key_append_byID.cpp $(CFLAGS)

# Appending by dataset name test
key_byName:	POST_key_append_byName.o
	$(CC) POST_key_append_byName.o API.o -o append_key_byName.out $(CFLAGS)

POST_key_append_byName.o:
	$(CC) -c POST_key_append_byName.cpp $(CFLAGS)

# Email test
email:	POST_email.o
	$(CC) POST_email.o API.o -o email.out $(CFLAGS)

POST_email.o:
	$(CC) -c POST_email.cpp $(CFLAGS)

# Appending by dataset ID test
email_byID:	POST_email_append_byID.o
	$(CC) $(CFLAGS) POST_email_append_byID.o API.o -o append_email_byID.out -lcurl

POST_email_append_byID.o:
	$(CC) -c POST_email_append_byID.cpp $(CFLAGS)

# Appending by dataset name test
email_byName:	POST_email_append_byName.o
	$(CC) $(CFLAGS) POST_email_append_byName.o API.o -o append_email_byName.out -lcurl

POST_email_append_byName.o:
	$(CC) -c POST_email_append_byName.cpp $(CFLAGS)

clean:
	rm *.out
	rm *.o