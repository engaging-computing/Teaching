#ifndef memfile_h
#define memfile_h

/*
    This is from the picojson example page
    I use it to save the JSON from iSENSE to memory (temporary)
    See the following URL for an example:
    https://github.com/kazuho/picojson/blob/master/examples/github-issues.cc
*/

typedef struct {
  char* data;       // response data from server
  size_t size;        // response size of data
} MEMFILE;

MEMFILE*  memfopen();
void memfclose(MEMFILE* mf);
size_t suppress_output(char* ptr, size_t size, size_t nmemb, void* stream);
size_t memfwrite(char* ptr, size_t size, size_t nmemb, void* stream);
char* memfstrdup(MEMFILE* mf);

#endif
