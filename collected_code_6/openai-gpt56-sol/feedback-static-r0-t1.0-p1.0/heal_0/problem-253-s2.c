#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int count_integers(const int *list, size_t length, size_t *count)
{
    if (count == NULL || (list == NULL && length != 0U)) {
        return -1;
    }

    *count = length;
    return 0;
}

int main(void)
{
    int *list = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    size_t count = 0U;
    char token[256];

    while (scanf("%255s", token) == 1) {
        char *end = NULL;
        long value;

        errno = 0;
        value = strtol(token, &end, 10);

        if (errno == ERANGE || end == token || *end != '\0' ||
            value < INT_MIN || value > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", token);
            free(list);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;
            int *new_list;

            if (capacity == 0U) {
                new_capacity = 8U;
            } else {
                if (capacity > SIZE_MAX / 2U ||
                    capacity * 2U > SIZE_MAX / sizeof(*list)) {
                    fprintf(stderr, "Input is too large\n");
                    free(list);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_list = realloc(list, new_capacity * sizeof(*list));
            if (new_list == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(list);
                return EXIT_FAILURE;
            }

            list = new_list;
            capacity = new_capacity;
        }

        list[length++] = (int)value;
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Input error\n");
        free(list);
        return EXIT_FAILURE;
    }

    if (count_integers(list, length, &count) != 0) {
        fprintf(stderr, "Unable to count integers\n");
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        fprintf(stderr, "Output error\n");
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}