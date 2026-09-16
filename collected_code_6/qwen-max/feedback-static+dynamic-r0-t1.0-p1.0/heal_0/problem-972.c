#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple* first;
    Tuple* second;
} NestedTuple;

NestedTuple* concatenateTuples(Tuple* t1, Tuple* t2) {
    NestedTuple* result = (NestedTuple*)malloc(sizeof(NestedTuple));
    if (result == NULL) {
        return NULL;
    }
    result->first = t1;
    result->second = t2;
    return result;
}

int main() {
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};

    NestedTuple* nested = concatenateTuples(&t1, &t2);
    if (nested == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("((%d, %d), (%d, %d))\n", nested->first->first, nested->first->second, nested->second->first, nested->second->second);

    free(nested);
    return 0;
}