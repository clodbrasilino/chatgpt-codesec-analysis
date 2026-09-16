#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int sumTuples(Tuple *tupleList, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += tupleList[i].a + tupleList[i].b;
    }
    return sum;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}};
    int length = sizeof(tuples) / sizeof(tuples[0]);
    int result = sumTuples(tuples, length);
    printf("Sum: %d\n", result);
    return 0;
}