#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int a;
    int b;
} Tuple;

void removeMatchingTuples(Tuple *tuple1, int size1, Tuple *tuple2, int size2) {
    int i, j;
    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++) {
            if(tuple1[i].a == tuple2[j].a && tuple1[i].b == tuple2[j].b) {
                tuple1[i].a = tuple1[i].b = -1;
                tuple2[j].a = tuple2[j].b = -1;
            }
        }
    }
}

int main() {
    Tuple tuple1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuple2[] = {{3, 4}, {5, 6}, {7, 8}};
    int size1 = sizeof(tuple1) / sizeof(Tuple);
    int size2 = sizeof(tuple2) / sizeof(Tuple);

    removeMatchingTuples(tuple1, size1, tuple2, size2);

    int i;
    printf("Tuple 1:\n");
    for(i = 0; i < size1; i++) {
        if(tuple1[i].a != -1 && tuple1[i].b != -1)
            printf("(%d, %d)\n", tuple1[i].a, tuple1[i].b);
    }

    printf("Tuple 2:\n");
    for(i = 0; i < size2; i++) {
        if(tuple2[i].a != -1 && tuple2[i].b != -1)
            printf("(%d, %d)\n", tuple2[i].a, tuple2[i].b);
    }

    return 0;
}