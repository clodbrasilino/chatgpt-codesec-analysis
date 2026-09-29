#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int first;
    int second;
};

struct TupleList {
    struct Tuple* tuples;
    size_t size;
};

struct TupleGroup {
    int* firstElements;
    size_t size;
};

struct TupleGroup groupFirstElementsBySecond(struct TupleList* tupleList, int second) {
    struct TupleGroup tupleGroup;
    tupleGroup.size = 0;

    for(size_t i = 0; i < tupleList->size; ++i) {
        if(tupleList->tuples[i].second == second) 
            tupleGroup.size++;
    }

    tupleGroup.firstElements = malloc(sizeof(int) * tupleGroup.size);

    if(tupleGroup.firstElements == NULL) 
        return tupleGroup;

    size_t index = 0;
    for(size_t i = 0; i < tupleList->size; ++i) {
        if(tupleList->tuples[i].second == second) 
            tupleGroup.firstElements[index++] = tupleList->tuples[i].first;
    }

    return tupleGroup;
}

int main() {
    struct Tuple tuples[] = {{1, 2}, {3, 2}, {5, 1}, {7, 2}};
    struct TupleList tupleList = {tuples, sizeof(tuples) / sizeof(tuples[0])};

    struct TupleGroup tupleGroup = groupFirstElementsBySecond(&tupleList, 2);

    if(tupleGroup.firstElements != NULL) {
        for(size_t i = 0; i < tupleGroup.size; ++i) {
            printf("%d ", tupleGroup.firstElements[i]);
        }
        free(tupleGroup.firstElements);
    }
    return 0;
}