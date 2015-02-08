# Makefile for the iSENSE projects involving C++
# Designed to quickly compile the C++ code
CC = g++

# NOTES: -lcurl is required. std=c++11 is also needed for to_string
CFLAGS = -Wall -Werror -pedantic -std=c++11 -lcurl

# Makes all of the C++ projects
all:	key key_byID key_byName email email_byID email_byName search datasets tests

# Contributor key test
key:	POST_key.o API.o
	$(CC) POST_key.o API.o -o key.out $(CFLAGS)

POST_key.o:	POST_key.cpp
	$(CC) -c POST_key.cpp $(CFLAGS)

API.o:	API.cpp
	$(CC) -c API.cpp $(CFLAGS)

# Appending by dataset ID test
key_byID:	POST_key_append_byID.o API.o
	$(CC) POST_key_append_byID.o API.o -o append_key_byID.out $(CFLAGS)

POST_key_append_byID.o:
	$(CC) -c POST_key_append_byID.cpp $(CFLAGS)

# Appending by dataset name test
key_byName:	POST_key_append_byName.o API.o
	$(CC) POST_key_append_byName.o API.o -o append_key_byName.out $(CFLAGS)

POST_key_append_byName.o:
	$(CC) -c POST_key_append_byName.cpp $(CFLAGS)

# Email test
email:	POST_email.o API.o
	$(CC) POST_email.o API.o -o email.out $(CFLAGS)

POST_email.o:
	$(CC) -c POST_email.cpp $(CFLAGS)

# Appending by dataset ID test
email_byID:	POST_email_append_byID.o API.o
	$(CC) POST_email_append_byID.o API.o -o append_email_byID.out $(CFLAGS)

POST_email_append_byID.o:
	$(CC) -c POST_email_append_byID.cpp $(CFLAGS)

# Appending by dataset name test
email_byName:	POST_email_append_byName.o API.o
	$(CC) POST_email_append_byName.o API.o -o append_email_byName.out $(CFLAGS)

POST_email_append_byName.o:
	$(CC) -c POST_email_append_byName.cpp $(CFLAGS)

# Search iSENSE test
search:	GET_search.o API.o
	$(CC) GET_search.o API.o -o search.out $(CFLAGS)

GET_search.o:
	$(CC) -c GET_search.cpp $(CFLAGS)

# Pulling down datasets test
datasets:	GET_Datasets.o API.o
	$(CC) GET_Datasets.o API.o -o datasets.out $(CFLAGS)

GET_Datasets.o:
	$(CC) -c GET_Datasets.cpp $(CFLAGS)

# Quick test of the API
api_tests:	POST_API_Test.o API.o
	$(CC) POST_API_Test.o -o API.o api.out $(CFLAGS)

POST_API_Test.o:
	$(CC) -c POST_API_Test.o $(CFLAGS)

# Unit tests for the iSENSE code. Not yet implemented - future idea
tests:	tests.o API.o
	$(CC) tests.o API.o -o tests.out $(CFLAGS)

tests.o:
	$(CC) -c tests.cpp $(CFLAGS)

clean:
	rm *.out
	rm *.o