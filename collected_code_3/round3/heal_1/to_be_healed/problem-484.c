#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

Tuple* removeMatchingTuples(Tuple* tuple1, int size1, Tuple* tuple2, int size2, int* newSize) {
    Tuple* result = (Tuple*)malloc(sizeof(Tuple) * size1);
    int index = 0;

    for(int i = 0; i < size1; i++) {
        int found = 0;
        for(int j = 0; j < size2; j++) {
            if(tuple1[i].x == tuple2[j].x && tuple1[i].y == tuple2[j].y) {
                found = 1;
                break;
            }
        }
        if(!found) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
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
        printf("(%d, %d)\n", result[i].x, result[i].y);
    }

    free(result);
    return 0;
}