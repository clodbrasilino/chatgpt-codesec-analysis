#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_column(const char *tuple, size_t tuple_length, size_t column)
{
    const char *start;
    const char *end;
    size_t remaining;
    size_t current;
    size_t length;
    char *result;

    if (tuple == NULL) {
        return NULL;
    }

    start = tuple;
    remaining = tuple_length;

    for (current = 0; current < column; ++current) {
        end = memchr(start, ':', remaining);
        if (end == NULL) {
            return NULL;
        }

        length = (size_t)(end - start);

        if (length == remaining) {
            return NULL;
        }

        start = end + 1;
        remaining -= length + 1;
    }

    end = memchr(start, ':', remaining);
    length = end == NULL ? remaining : (size_t)(end - start);

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
    char *value = get_column(tuple, tuple_length, 1);

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