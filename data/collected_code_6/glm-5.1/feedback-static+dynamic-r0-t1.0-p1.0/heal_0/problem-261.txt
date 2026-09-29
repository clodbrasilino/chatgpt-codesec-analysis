#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

int divide_tuples(Tuple a, Tuple b, double *result) {
    if (b.numerator == 0 || a.denominator == 0 || b.denominator == 0) {
        return -1;
    }
    long long intermediate_numerator = (long long)a.numerator * b.denominator;
    long long intermediate_denominator = (long long)a.denominator * b.numerator;
    if (intermediate_denominator == 0) {
        return -1;
    }
    *result = (double)intermediate_numerator / (double)intermediate_denominator;
    return 0;
}

int main() {
    Tuple t1 = {10, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {0, 5};
    Tuple t4 = {5, 0};
    Tuple t5 = {2, 3};

    double res;

    if (divide_tuples(t1, t2, &res) == 0) {
        printf("%d/%d / %d/%d = %f\n", t1.numerator, t1.denominator, t2.numerator, t2.denominator, res);
    } else {
        printf("Error dividing t1 and t2\n");
    }

    if (divide_tuples(t1, t3, &res) == 0) {
        printf("%d/%d / %d/%d = %f\n", t1.numerator, t1.denominator, t3.numerator, t3.denominator, res);
    } else {
        printf("Error dividing t1 and t3\n");
    }

    if (divide_tuples(t1, t4, &res) == 0) {
        printf("%d/%d / %d/%d = %f\n", t1.numerator, t1.denominator, t4.numerator, t4.denominator, res);
    } else {
        printf("Error dividing t1 and t4\n");
    }

    if (divide_tuples(t5, t5, &res) == 0) {
        printf("%d/%d / %d/%d = %f\n", t5.numerator, t5.denominator, t5.numerator, t5.denominator, res);
    } else {
        printf("Error dividing t5 and t5\n");
    }

    return 0;
}