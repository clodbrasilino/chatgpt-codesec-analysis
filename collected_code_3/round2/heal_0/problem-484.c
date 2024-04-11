#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* removeMatchingTuples(Tuple* tuple1, int size1, Tuple* tuple2, int size2, int* newSize) {
    Tuple* result = (Tuple*)malloc(sizeof(Tuple) * size1);
    int index = 0;

    for(int i = 0; i < size1; i++) {
        int found = 0;
        for(int j = 0; j < size2; j++) {
            if(tuple1[i].a == tuple2[j].a && tuple1[i].b == tuple2[j].b) {
                found = 1;
                break;
            }
        }
        if(!found) {
            result[index++] = tuple1[i];
        }
    }

    *newSize = index;
    return result;
}

int main() {
    Tuple tuple1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuple2[] = {{3, 4}, {7, 8}};
    int newSize = 0;

    Tuple* result = removeMatchingTuples(tuple1, 3, tuple2, 2, &newSize);

    for(int i = 0; i < newSize; i++) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }

    free(result);
    return 0;
}