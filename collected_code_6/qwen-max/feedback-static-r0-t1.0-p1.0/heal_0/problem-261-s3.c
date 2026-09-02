#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

Tuple divideTuples(Tuple t1, Tuple t2) {
    if (t2.denominator == 0) {
        fprintf(stderr, "Error: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    Tuple result;
    result.numerator = t1.numerator * t2.denominator;
    result.denominator = t1.denominator * t2.numerator;
    return result;
}

int main() {
    Tuple t1 = {6, 4};
    Tuple t2 = {3, 2};

    Tuple result = divideTuples(t1, t2);

    printf("Result: %d/%d\n", result.numerator, result.denominator);

    return 0;
}