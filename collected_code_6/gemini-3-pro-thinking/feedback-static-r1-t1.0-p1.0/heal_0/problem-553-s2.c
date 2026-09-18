#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

int tuple_to_double(const Tuple *tuple, double *result) {
    if (tuple == NULL || result == NULL) {
        return -1;
    }
    if (tuple->denominator == 0) {
        return -1;
    }
    
    *result = (double)tuple->numerator / (double)tuple->denominator;
    
    return 0;
}

int main(void) {
    Tuple valid_tuple = {3, 4};
    double converted_value = 0.0;

    if (tuple_to_double(&valid_tuple, &converted_value) == 0) {
        printf("%f\n", converted_value);
    } else {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    Tuple invalid_tuple = {1, 0};
    if (tuple_to_double(&invalid_tuple, &converted_value) == 0) {
        printf("%f\n", converted_value);
    } else {
        fprintf(stderr, "Conversion failed\n");
    }

    return EXIT_SUCCESS;
}