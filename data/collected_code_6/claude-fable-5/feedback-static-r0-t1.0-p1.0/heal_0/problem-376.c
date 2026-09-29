#include <stdio.h>
#include <stdlib.h>

#define TUPLE_SIZE 10
#define CUSTOM_VALUE -1

int replace_duplicates(int *tuple, size_t size, int custom_value)
{
    size_t i;
    size_t j;

    if (tuple == NULL || size == 0U) {
        return -1;
    }

    for (i = 0U; i < size; i++) {
        if (tuple[i] == custom_value) {
            continue;
        }
        for (j = i + 1U; j < size; j++) {
            if (tuple[j] == tuple[i]) {
                tuple[j] = custom_value;
            }
        }
    }

    return 0;
}

int print_tuple(const int *tuple, size_t size)
{
    size_t i;

    if (tuple == NULL || size == 0U) {
        return -1;
    }

    if (printf("(") < 0) {
        return -1;
    }
    for (i = 0U; i < size; i++) {
        if (i < size - 1U) {
            if (printf("%d, ", tuple[i]) < 0) {
                return -1;
            }
        } else {
            if (printf("%d", tuple[i]) < 0) {
                return -1;
            }
        }
    }
    if (printf(")\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int tuple[TUPLE_SIZE] = { 1, 3, 5, 3, 7, 1, 9, 5, 3, 11 };
    int result;

    result = print_tuple(tuple, TUPLE_SIZE);
    if (result != 0) {
        (void)fprintf(stderr, "Failed to print tuple\n");
        return EXIT_FAILURE;
    }

    result = replace_duplicates(tuple, TUPLE_SIZE, CUSTOM_VALUE);
    if (result != 0) {
        (void)fprintf(stderr, "Failed to replace duplicates\n");
        return EXIT_FAILURE;
    }

    result = print_tuple(tuple, TUPLE_SIZE);
    if (result != 0) {
        (void)fprintf(stderr, "Failed to print tuple\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}