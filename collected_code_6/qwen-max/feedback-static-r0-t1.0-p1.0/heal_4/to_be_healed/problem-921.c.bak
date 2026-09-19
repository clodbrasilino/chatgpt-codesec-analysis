#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const int *data;
    size_t length;
} TupleChunk;

TupleChunk *create_chunk(const int *dataArray, size_t n, size_t chunkSize) {
    if (chunkSize == 0 || n % chunkSize != 0) {
        return NULL;
    }

    size_t numChunks = n / chunkSize;
    TupleChunk *chunks = (TupleChunk *)malloc(numChunks * sizeof(TupleChunk));
    if (chunks == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < numChunks; ++i) {
        chunks[i].data = (int *)malloc(chunkSize * sizeof(int));
        if (chunks[i].data == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free(chunks[j].data);
            }
            free(chunks);
            return NULL;
        }
        chunks[i].length = chunkSize;
        memcpy(chunks[i].data, &dataArray[i * chunkSize], chunkSize * sizeof(int));
    }

    return chunks;
}

void free_chunks(TupleChunk *chunks, size_t numChunks) {
    for (size_t i = 0; i < numChunks; ++i) {
        free(chunks[i].data);
    }
    free(chunks);
}

int main() {
    const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n = 10;
    size_t chunkSize = 4;

    /* Possible weaknesses found:
     *  Assignment 'chunks=create_chunk(data,n,chunkSize)', assigned value is 0
     *  Calling function 'create_chunk' returns 0
     */
    TupleChunk *chunks = create_chunk(data, n, chunkSize);
    /* Possible weaknesses found:
     *  Condition 'chunks==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'chunks==NULL' is always true
     */
    if (chunks == NULL) {
        fprintf(stderr, "Failed to create chunks\n");
        return 1;
    }

    size_t numChunks = n / chunkSize;
    for (size_t i = 0; i < numChunks; ++i) {
        for (size_t j = 0; j < chunks[i].length; ++j) {
            printf("%d ", chunks[i].data[j]);
        }
        printf("\n");
    }

    free_chunks(chunks, numChunks);
    return 0;
}