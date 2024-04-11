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

void sortTuples(Tuple* tuples, int count) {
    qsort(tuples, count, sizeof(Tuple), compare);
}

int main() {
    Tuple tuples[] = {
        {"apple", "fruit"},
        {"carrot", "vegetable"},
        {"banana", "fruit"},
        {"eggplant", "vegetable"}
    };

    int count = sizeof(tuples) / sizeof(Tuple);

    sortTuples(tuples, count);

    for(int i = 0; i < count; i++) {
        printf("%s, %s\n", tuples[i].first, tuples[i].second);
    }

    return 0;
}