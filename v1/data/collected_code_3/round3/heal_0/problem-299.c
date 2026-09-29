#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

int maxAggregate(Tuple* tuples, int size) {
    int max = tuples[0].a + tuples[0].b;
    for(int i = 1; i < size; i++) {
        int current = tuples[i].a + tuples[i].b;
        if(current > max) {
            max = current;
        }
    }
    return max;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int size = sizeof(tuples) / sizeof(Tuple);
    int max = maxAggregate(tuples, size);
    printf("Max aggregate is %d\n", max);
    return 0;
}