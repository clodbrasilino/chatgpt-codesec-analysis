#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int *convert_string_tuple_to_int(const char **str_tuple, size_t size) {
    if (str_tuple == NULL || size == 0) {
        return NULL;
    }

    int *int_tuple = (int *)malloc(size * sizeof(int));
    if (int_tuple == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (str_tuple[i] == NULL) {
            free(int_tuple);
            return NULL;
        }

        char *endptr;
        errno = 0;
        long val = strtol(str_tuple[i], &endptr, 10);

        if (endptr == str_tuple[i] || *endptr != '\0' || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            free(int_tuple);
            return NULL;
        }

        int_tuple[i] = (int)val;
    }

    return int_tuple;
}

int main(void) {
    const char *str_tuple[] = {"10", "20", "30", "40"};
    size_t size = sizeof(str_tuple) / sizeof(str_tuple[0]);

    int *int_tuple = convert_string_tuple_to_int(str_tuple, size);
    if (int_tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", int_tuple[i]);
    }
    printf("\n");

    free(int_tuple);

    return EXIT_SUCCESS;
}