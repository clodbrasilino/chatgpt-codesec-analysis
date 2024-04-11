#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

Tuple* removeMatchingTuples(Tuple* tuple1, int size1, Tuple* tuple2, int size2, int* newSize) {
    Tuple* result = (Tuple*)malloc(sizeof(Tuple) * size1);
    int index = 0;

    for(int i = 0; i < size1; i++) {
        int match = 0;
        for(int j = 0; j < size2; j++) {
            if(tuple1[i].first == tuple2[j].first && tuple1[i].second == tuple2[j].second) {
                match = 1;
                break;
            }
        }
        if(!match) {
            result[index++] = tuple1[i];
        }
    }

    *newSize = index;
    return result;
}

int main() {
    Tuple tuple1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuple2[] = {{3, 4}, {7, 8}};
    int size1 = sizeof(tuple1) / sizeof(Tuple);
    int size2 = sizeof(tuple2) / sizeof(Tuple);
    int newSize;

    Tuple* result = removeMatchingTuples(tuple1, size1, tuple2, size2, &newSize);

    for(int i = 0; i < newSize; i++) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    free(result);
    return 0;
}