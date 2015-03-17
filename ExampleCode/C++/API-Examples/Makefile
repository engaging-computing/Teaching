# Makefile for the iSENSE projects involving C++
# Designed to quickly compile the C++ code (only if files are changed)
CC = g++

# NOTES: -lcurl is required. -std=c++0x is also needed for to_string.
CFLAGS = -Wall -Werror -pedantic -std=c++0x -lcurl

# Makes all of the C++ projects, appends a ".out" for easy removal in make clean
all:	key.out append_key_byName.out email.out  \
	append_email_byName.out search.out datasets.out

# Contributor key test
key.out:	POST_key.o API.o
	$(CC) POST_key.o API.o -o key.out $(CFLAGS)

POST_key.o:	POST_key.cpp
	$(CC) -c POST_key.cpp $(CFLAGS)

API.o:	API.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c API.cpp $(CFLAGS)

# Appending by dataset ID test
# Setting IDs is now private, so these are just here for testing purposes
append_key_byID.out:	POST_key_append_byID.o API.o
	$(CC) POST_key_append_byID.o API.o -o append_key_byID.out $(CFLAGS)

POST_key_append_byID.o:	POST_key_append_byID.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c POST_key_append_byID.cpp $(CFLAGS)

# Appending by dataset name test
append_key_byName.out:	POST_key_append_byName.o API.o
	$(CC) POST_key_append_byName.o API.o -o append_key_byName.out $(CFLAGS)

POST_key_append_byName.o:	POST_key_append_byName.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c POST_key_append_byName.cpp $(CFLAGS)

# Email test
email.out:	POST_email.o API.o
	$(CC) POST_email.o API.o -o email.out $(CFLAGS)

POST_email.o:	POST_email.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c POST_email.cpp $(CFLAGS)

# Appending by dataset ID test
# Setting IDs is now private, so these are just here for testing purposes
append_email_byID.out:	POST_email_append_byID.o API.o
	$(CC) POST_email_append_byID.o API.o -o append_email_byID.out $(CFLAGS)

POST_email_append_byID.o: POST_email_append_byID.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c POST_email_append_byID.cpp $(CFLAGS)

# Appending by dataset name test
append_email_byName.out:	POST_email_append_byName.o API.o
	$(CC) POST_email_append_byName.o API.o -o append_email_byName.out $(CFLAGS)

POST_email_append_byName.o:	POST_email_append_byName.cpp API.o include/API.h include/memfile.h include/picojson.h
	$(CC) -c POST_email_append_byName.cpp $(CFLAGS)

# Search iSENSE test
search.out:	GET_search.o API.o
	$(CC) GET_search.o API.o -o search.out $(CFLAGS)

GET_search.o: 	GET_search.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c GET_search.cpp $(CFLAGS)

# Pulling down datasets test
datasets.out:	GET_Datasets.o API.o
	$(CC) GET_Datasets.o API.o -o datasets.out $(CFLAGS)

GET_Datasets.o: GET_Datasets.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c GET_Datasets.cpp $(CFLAGS)

# Quick test of the API - *** not included in all ***.
api.out:	POST_API_Test.o API.o
	$(CC) POST_API_Test.o API.o -o api.out $(CFLAGS)

POST_API_Test.o: POST_API_Test.cpp include/API.h include/memfile.h include/picojson.h
	$(CC) -c POST_API_Test.cpp $(CFLAGS)

clean:
	rm *.o
	rm *.out
