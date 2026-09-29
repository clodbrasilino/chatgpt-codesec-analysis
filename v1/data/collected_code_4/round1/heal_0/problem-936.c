#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

uint16_t *rearrangeTuples(uint16_t *byteArray, Tuple *tuples, size_t tupleCount) {
    uint16_t *rearrangedArray = malloc(tupleCount * sizeof(uint16_t));
    if (!rearrangedArray) {
        fprintf(stderr, "Failed to allocate memory for rearrangedArray\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < tupleCount; ++i) {
        if (tuples[i].first > tupleCount || tuples[i].second > tupleCount) {
            fprintf(stderr, "Tuple values exceeded tuple count\n");
            free(rearrangedArray);
            exit(EXIT_FAILURE);
        }
        rearrangedArray[i] = byteArray[tuples[i].first];
        byteArray[tuples[i].first] = byteArray[tuples[i].second];
    }

    return rearrangedArray;
}

int main() {

    uint16_t byteArray[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Tuple tuples[] = {{0, 3}, {2, 7}, {1, 6}};
    size_t tupleCount = sizeof(tuples) / sizeof(Tuple);
    uint16_t *rearrangedArray = rearrangeTuples(byteArray, tuples, tupleCount);
    for (size_t i = 0; i < tupleCount; ++i) {
        printf("%d\n", rearrangedArray[i]);
    }

    free(rearrangedArray);
    return 0;
}