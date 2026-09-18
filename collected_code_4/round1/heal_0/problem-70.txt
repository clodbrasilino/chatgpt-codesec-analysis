#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int size;
    int *data;
} Tuple;

bool hasEqualLength(Tuple* tuples, int numTuples) {
    if (numTuples == 0)
        return true;

    int size = tuples[0].size;

    for(int i=1; i<numTuples; i++) {
        if(tuples[i].size != size)
            return false;
    }

    return true;
}

int main() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6, 7};
    int data3[] = {8, 9, 10, 11};

    Tuple tuple1 = { .size = sizeof(data1)/sizeof(data1[0]), .data = data1 };
    Tuple tuple2 = { .size = sizeof(data2)/sizeof(data2[0]), .data = data2 };
    Tuple tuple3 = { .size = sizeof(data3)/sizeof(data3[0]), .data = data3 };

    Tuple tuples[] = { tuple1, tuple2, tuple3 };

    if (hasEqualLength(tuples, sizeof(tuples)/sizeof(tuples[0]))) {
        printf("All tuples have equal length.\n");
    } else {
        printf("All tuples do not have equal length.\n");
    }

    return 0;
}