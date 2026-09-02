#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x, y;
} Tuple;

int compareTuples(const void *a, const void *b) {
    return ((Tuple *)a)->x - ((Tuple *)b)->x ? ((Tuple *)a)->x - ((Tuple *)b)->x : ((Tuple *)a)->y - ((Tuple *)b)->y;
}

int countUniqueTuples(int *tupleList, size_t tupleCount, int *outUniqueCount) {
    if (tupleCount == 0 || outUniqueCount == NULL) {
        return -1;
    }

    Tuple *tuples = (Tuple *)malloc(tupleCount * sizeof(Tuple));
    if (tuples == NULL) {
        return -2;
    }

    for (size_t i = 0; i < tupleCount; ++i) {
        tuples[i].x = tupleList[i * 2];
        tuples[i].y = tupleList[i * 2 + 1];
    }

    qsort(tuples, tupleCount, sizeof(Tuple), compareTuples);

    size_t uniqueTuples = 1;
    for (size_t i = 1; i < tupleCount; ++i) {
        if (tuples[i].x != tuples[i - 1].x || tuples[i].y != tuples[i - 1].y) {
            uniqueTuples++;
        }
    }

    *outUniqueCount = uniqueTuples;
    free(tuples);
    return 0;
}

int main() {
    int list[] = {1, 3, 2, 4, 1, 3, 2, 5, 6, 7, 6, 7};
    size_t listSize = sizeof(list) / sizeof(list[0]);
    int uniqueCount = 0;

    if (countUniqueTuples(list, listSize / 2, &uniqueCount) == 0) {
        printf("Number of unique tuples: %d\n", uniqueCount);
    } else {
        printf("An error occurred.\n");
    }

    return 0;
}