#include <stdio.h>

typedef struct {
    int a;
    int b;
} Tuple;

int sum_tuple_elements(Tuple* tuples, int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += tuples[i].a + tuples[i].b;
    }
    return sum;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}};
    int size = sizeof(tuples) / sizeof(Tuple);
    int sum = sum_tuple_elements(tuples, size);
    printf("Sum of tuple elements: %d\n", sum);
    return 0;
}