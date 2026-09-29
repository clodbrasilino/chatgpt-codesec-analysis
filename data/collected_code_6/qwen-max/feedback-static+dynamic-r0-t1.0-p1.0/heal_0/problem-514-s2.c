#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int sum_tuples(Tuple *tuples, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += tuples[i].a + tuples[i].b;
    }
    return sum;
}

int main() {
    Tuple sample_tuples[] = {{1, 2}, {3, 4}, {5, 6}};
    int length = sizeof(sample_tuples) / sizeof(sample_tuples[0]);
    int result = sum_tuples(sample_tuples, length);
    printf("%d\n", result);
    return 0;
}