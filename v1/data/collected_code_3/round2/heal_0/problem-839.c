#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TUPLES 100
#define MAX_STRING 100

typedef struct {
    char first[MAX_STRING];
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    Tuple *tupleA = (Tuple *)a;
    Tuple *tupleB = (Tuple *)b;
    return strcmp(tupleA->first, tupleB->first);
}

void sortTuples(Tuple *tuples, int size) {
    qsort(tuples, size, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[MAX_TUPLES];
    int size = 0;

    strcpy(tuples[size].first, "apple");
    tuples[size].second = 1;
    size++;

    strcpy(tuples[size].first, "banana");
    tuples[size].second = 2;
    size++;

    strcpy(tuples[size].first, "grape");
    tuples[size].second = 3;
    size++;

    sortTuples(tuples, size);

    for(int i = 0; i < size; i++) {
        printf("%s %d\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}