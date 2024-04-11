#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;

int compare(const void* a, const void* b) {
    Tuple* tupleA = (Tuple*) a;
    Tuple* tupleB = (Tuple*) b;
    return strcmp(tupleA->first, tupleB->first);
}

void sortTuples(Tuple* tuples, int size) {
    qsort(tuples, size, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {{"apple", "fruit"}, {"carrot", "vegetable"}, {"banana", "fruit"}};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    sortTuples(tuples, size);

    for(int i = 0; i < size; i++) {
        printf("%s: %s\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}