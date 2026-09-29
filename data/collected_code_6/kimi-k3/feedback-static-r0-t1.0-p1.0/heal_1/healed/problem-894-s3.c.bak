#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

typedef struct {
    float *data;
    size_t size;
} FloatTuple;

int string_to_float_tuple(const char *str, FloatTuple *tuple) {
    char *str_copy = NULL;
    char *token = NULL;
    char *endptr = NULL;
    float *temp_array = NULL;
    float *new_array = NULL;
    size_t capacity = 10;
    size_t count = 0;

    if (str == NULL || tuple == NULL) {
        return -1;
    }

    tuple->data = NULL;
    tuple->size = 0;

    str_copy = malloc(strlen(str) + 1);
    if (str_copy == NULL) {
        return -1;
    }
    strcpy(str_copy, str);

    temp_array = malloc(capacity * sizeof(float));
    if (temp_array == NULL) {
        free(str_copy);
        return -1;
    }

    token = strtok(str_copy, " ,()");
    while (token != NULL) {
        float value;
        errno = 0;
        value = strtof(token, &endptr);

        if (errno != 0 || endptr == token || *endptr != '\0' || !isfinite(value)) {
            free(temp_array);
            free(str_copy);
            return -1;
        }

        if (count >= capacity) {
            capacity *= 2;
            new_array = realloc(temp_array, capacity * sizeof(float));
            if (new_array == NULL) {
                free(temp_array);
                free(str_copy);
                return -1;
            }
            temp_array = new_array;
        }

        temp_array[count++] = value;
        token = strtok(NULL, " ,()");
    }

    if (count == 0) {
        free(temp_array);
        tuple->data = NULL;
        tuple->size = 0;
    } else {
        new_array = realloc(temp_array, count * sizeof(float));
        if (new_array == NULL) {
            free(temp_array);
            free(str_copy);
            return -1;
        }
        tuple->data = new_array;
        tuple->size = count;
    }

    free(str_copy);
    return 0;
}

void free_float_tuple(FloatTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->size = 0;
    }
}

int main(void) {
    const char *input = "(1.5, 2.7, 3.14, 4.0, 5.5)";
    FloatTuple tuple;
    size_t i;

    if (string_to_float_tuple(input, &tuple) != 0) {
        fprintf(stderr, "Error: Failed to convert string to float tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple size: %zu\n", tuple.size);
    printf("Values: ");
    for (i = 0; i < tuple.size; i++) {
        printf("%.2f ", tuple.data[i]);
    }
    printf("\n");

    free_float_tuple(&tuple);
    return EXIT_SUCCESS;
}