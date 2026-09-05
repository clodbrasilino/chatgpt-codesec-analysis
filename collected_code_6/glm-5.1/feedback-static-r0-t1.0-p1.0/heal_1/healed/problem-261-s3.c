#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

typedef struct {
    int status;
    int quotient;
} DivResult;

DivResult divide_tuples(const Tuple *t1, const Tuple *t2) {
    DivResult result = {0, 0};

    if (t1 == NULL || t2 == NULL) {
        result.status = -1;
        return result;
    }

    if (t1->denominator == 0 || t2->denominator == 0 || t2->numerator == 0) {
        result.status = -2;
        return result;
    }

    int a = t1->numerator * t2->denominator;
    int b = t1->denominator * t2->numerator;

    if (b == 0) {
        result.status = -2;
        return result;
    }

    if (a == INT_MIN && b == -1) {
        result.status = -3;
        return result;
    }

    result.quotient = a / b;
    result.status = 1;
    return result;
}

int main(void) {
    Tuple t1 = {10, 2};
    Tuple t2 = {5, 1};
    Tuple t3 = {1, 0};
    Tuple t4 = {0, 5};

    DivResult r1 = divide_tuples(&t1, &t2);
    DivResult r2 = divide_tuples(&t1, &t3);
    DivResult r3 = divide_tuples(NULL, &t2);
    DivResult r4 = divide_tuples(&t1, &t4);

    if (r1.status == 1) printf("t1 / t2 = %d\n", r1.quotient);
    if (r2.status != 1) printf("t1 / t3 failed with status %d\n", r2.status);
    if (r3.status != 1) printf("NULL / t2 failed with status %d\n", r3.status);
    if (r4.status == 1) printf("t1 / t4 = %d\n", r4.quotient);

    return EXIT_SUCCESS;
}