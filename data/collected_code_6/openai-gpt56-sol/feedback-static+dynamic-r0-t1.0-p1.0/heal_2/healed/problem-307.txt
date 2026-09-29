#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_column(const char *tuple, size_t tuple_length, size_t column)
{
    const char *start;
    const char *end;
    const char *limit;
    char *result;
    size_t current = 0;
    size_t length;

    if (tuple == NULL || tuple_length == SIZE_MAX) {
        return NULL;
    }

    start = tuple;
    limit = tuple + tuple_length;

    while (current < column) {
        end = memchr(start, ':', (size_t)(limit - start));
        if (end == NULL) {
            return NULL;
        }

        start = end + 1;
        ++current;
    }

    end = memchr(start, ':', (size_t)(limit - start));
    length = end != NULL ? (size_t)(end - start) : (size_t)(limit - start);

    if (length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    if (length != 0) {
        memcpy(result, start, length);
    }

    result[length] = '\0';
    return result;
}

int main(void)
{
    static const char tuple[] = "alpha:beta:gamma";
    const size_t tuple_length = sizeof(tuple) - 1;
    const size_t column = 1;
    char *value = get_column(tuple, tuple_length, column);

    if (value == NULL) {
        fputs("Unable to get column\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", value) < 0) {
        free(value);
        return EXIT_FAILURE;
    }

    free(value);
    return EXIT_SUCCESS;
}