#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

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
    char *line = NULL;
    size_t line_capacity = 0U;
    ssize_t line_length;

    while ((line_length = getline(&line, &line_capacity, stdin)) != -1) {
        char *cursor = line;
        /* Possible weaknesses found:
         *  Variable 'limit' can be declared as pointer to const [constVariablePointer]
         */
        char *limit = line + (size_t)line_length;

        while (cursor < limit) {
            char *end = NULL;
            long value;

            errno = 0;
            value = strtol(cursor, &end, 10);

            if (cursor == end) {
                break;
            }

            if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
                free(line);
                free(list);
                return EXIT_FAILURE;
            }

            if (length == capacity) {
                size_t new_capacity;
                int *temporary;

                if (capacity == 0U) {
                    new_capacity = 8U;
                } else {
                    if (capacity > SIZE_MAX / 2U) {
                        free(line);
                        free(list);
                        return EXIT_FAILURE;
                    }
                    new_capacity = capacity * 2U;
                }

                if (new_capacity > SIZE_MAX / sizeof *list) {
                    free(line);
                    free(list);
                    return EXIT_FAILURE;
                }

                temporary = realloc(list, new_capacity * sizeof *list);
                if (temporary == NULL) {
                    free(line);
                    free(list);
                    return EXIT_FAILURE;
                }

                list = temporary;
                capacity = new_capacity;
            }

            list[length++] = (int)value;
            cursor = end;
        }
    }

    free(line);

    if (ferror(stdin)) {
        free(list);
        return EXIT_FAILURE;
    }

    if (count_integers(list, length, &count) != 0) {
        free(list);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        free(list);
        return EXIT_FAILURE;
    }

    free(list);
    return EXIT_SUCCESS;
}