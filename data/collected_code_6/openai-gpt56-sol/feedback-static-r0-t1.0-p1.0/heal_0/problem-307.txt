#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_column(const char *tuple, size_t column)
{
    const char *start;
    const char *end;
    char *result;
    size_t current = 0;
    size_t length;

    if (tuple == NULL) {
        return NULL;
    }

    start = tuple;

    while (current < column) {
        start = strchr(start, ':');
        if (start == NULL) {
            return NULL;
        }
        ++start;
        ++current;
    }

    end = strchr(start, ':');
    length = end != NULL ? (size_t)(end - start) : strlen(start);

    if (length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, start, length);
    result[length] = '\0';

    return result;
}

int main(void)
{
    const char *tuple = "alpha:beta:gamma";
    size_t column = 1;
    char *value = get_column(tuple, column);

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