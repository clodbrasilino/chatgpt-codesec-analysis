#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *data;
    int length;
} Tuple;

int areAllTuplesEqualLength(Tuple *tuples, int tupleCount) {
    int length = tuples[0].length;
    for (int i = 1; i < tupleCount; i++) {
        if (tuples[i].length != length) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int data3[] = {7, 8, 9};

    Tuple tuples[] = {
        {data1, sizeof(data1) / sizeof(int)},
        {data2, sizeof(data2) / sizeof(int)},
        {data3, sizeof(data3) / sizeof(int)}
    };

    if (areAllTuplesEqualLength(tuples, sizeof(tuples) / sizeof(Tuple))) {
        printf("All tuples have equal length.\n");
    } else {
        printf("All tuples do not have equal length.\n");
    }

    return 0;
}