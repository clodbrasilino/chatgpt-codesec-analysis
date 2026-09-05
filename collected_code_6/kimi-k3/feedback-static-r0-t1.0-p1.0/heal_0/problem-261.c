#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int divide_tuples(const Tuple *t, float *result) {
    if (t == NULL || result == NULL) {
        return -1;
    }
    if (t->b == 0) {
        return -1;
    }
    *result = (float)t->a / (float)t->b;
    return 0;
}

int main(void) {
    Tuple t1 = {10, 2};
    Tuple t2 = {7, 0};
    float result = 0.0f;

    if (divide_tuples(&t1, &result) == 0) {
        printf("Result: %.2f\n", result);
    } else {
        printf("Error: Invalid division\n");
    }

    if (divide_tuples(&t2, &result) == 0) {
        printf("Result: %.2f\n", result);
    } else {
        printf("Error: Invalid division\n");
    }

    return 0;
}