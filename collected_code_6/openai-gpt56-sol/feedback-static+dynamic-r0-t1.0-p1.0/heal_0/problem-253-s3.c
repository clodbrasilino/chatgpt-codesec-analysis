#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        char *cursor = buffer;

        for (;;) {
            char *end = NULL;
            long value;

            errno = 0;
            value = strtol(cursor, &end, 10);

            if (cursor == end) {
                break;
            }

            if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
                free(list);
                return EXIT_FAILURE;
            }

            if (length == capacity) {
                size_t new_capacity = capacity == 0U ? 8U : capacity * 2U;
                int *temporary;

                if (new_capacity < capacity ||
                    new_capacity > SIZE_MAX / sizeof *list) {
                    free(list);
                    return EXIT_FAILURE;
                }

                temporary = realloc(list, new_capacity * sizeof *list);
                if (temporary == NULL) {
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

    if (ferror(stdin) != 0) {
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