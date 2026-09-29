#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

bool convert_tuple_to_float(const Tuple *const tuple, double *const result) {
    if (tuple == NULL || result == NULL) {
        return false;
    }

    if (tuple->denominator == 0) {
        return false;
    }

    *result = (double)tuple->numerator / (double)tuple->denominator;
    
    return true;
}

int main(void) {
    Tuple valid_tuple = {3, 4};
    double converted_value = 0.0;

    if (convert_tuple_to_float(&valid_tuple, &converted_value)) {
        printf("%f\n", converted_value);
    } else {
        fprintf(stderr, "Invalid input or division by zero.\n");
        return EXIT_FAILURE;
    }

    Tuple invalid_tuple = {1, 0};
    if (convert_tuple_to_float(&invalid_tuple, &converted_value)) {
        printf("%f\n", converted_value);
    } else {
        fprintf(stderr, "Invalid input or division by zero.\n");
    }

    return EXIT_SUCCESS;
}