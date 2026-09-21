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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = end != NULL ? (size_t)(end - start) : strlen(start);

    if (length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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