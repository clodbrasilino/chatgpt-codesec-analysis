#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numerator;
    int denominator;
} Tuple;

float convert_tuple_to_float(const Tuple *tuple_ptr, int *error_flag) {
    if (tuple_ptr == NULL || error_flag == NULL) {
        return 0.0f;
    }

    *error_flag = 0;

    if (tuple_ptr->denominator == 0) {
        *error_flag = 1;
        return 0.0f;
    }

    return (float)tuple_ptr->numerator / (float)tuple_ptr->denominator;
}

int main(void) {
    Tuple valid_tuple = {10, 3};
    Tuple invalid_tuple = {5, 0};
    int error_state = 0;
    float value = 0.0f;

    value = convert_tuple_to_float(&valid_tuple, &error_state);

    if (error_state != 0) {
        printf("Conversion failed for valid_tuple\n");
        return EXIT_FAILURE;
    }

    printf("Valid tuple result: %f\n", value);

    value = convert_tuple_to_float(&invalid_tuple, &error_state);

    if (error_state != 0) {
        printf("Conversion failed for invalid_tuple (expected)\n");
    } else {
        printf("Invalid tuple result: %f\n", value);
    }

    return EXIT_SUCCESS;
}