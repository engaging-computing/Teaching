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

MEMFILE*  memfopen() {
    MEMFILE* mf = (MEMFILE*) malloc(sizeof(MEMFILE));
    mf->data = NULL;
    mf->size = 0;
    return mf;
}

void memfclose(MEMFILE* mf) {
    // Double check to make sure that mf exists.
    if(mf == NULL)
    {
        return;
    }

    // OK to free the char array
    if (mf != NULL && mf->data)
    {
        free(mf->data);
    }

    // And OK to free the structure
    free(mf);
}

size_t memfwrite(char* ptr, size_t size, size_t nmemb, void* stream) {
    MEMFILE* mf = (MEMFILE*) stream;
    int block = size * nmemb;

    if (!mf->data)
    {
        mf->data = (char*) malloc(block);
    }
    else
    {
        mf->data = (char*) realloc(mf->data, mf->size + block);
    }

    if (mf->data)
    {
        memcpy(mf->data + mf->size, ptr, block);
        mf->size += block;
    }

    return block;
}

char* memfstrdup(MEMFILE* mf)
{
    char* buf = (char*)malloc(mf->size + 1);
    memcpy(buf, mf->data, mf->size);
    buf[mf->size] = 0;

    return buf;
}

#endif