#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TUPLE_SIZE 4

bool divide_tuples(const double *tuple1, const double *tuple2, double *result, size_t size)
{
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL || result == NULL || size == 0U) {
        return false;
    }

    for (i = 0U; i < size; i++) {
        if (tuple2[i] == 0.0) {
            return false;
        }
        result[i] = tuple1[i] / tuple2[i];
    }

    return true;
}

int main(void)
{
    const double tuple1[TUPLE_SIZE] = { 10.0, 4.0, 6.0, 9.0 };
    const double tuple2[TUPLE_SIZE] = { 5.0, 5.0, 7.0, 3.0 };
    double result[TUPLE_SIZE] = { 0.0 };
    size_t i;

    if (!divide_tuples(tuple1, tuple2, result, TUPLE_SIZE)) {
        if (fprintf(stderr, "Error: division failed due to invalid input or division by zero.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Result: (") < 0) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < TUPLE_SIZE; i++) {
        if (printf("%.4f", result[i]) < 0) {
            return EXIT_FAILURE;
        }
        if (i < (TUPLE_SIZE - 1U)) {
            if (printf(", ") < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    if (printf(")\n") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}