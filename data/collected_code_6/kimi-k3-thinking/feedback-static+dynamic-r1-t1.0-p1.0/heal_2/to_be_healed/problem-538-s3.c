#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 4096

char *string_list_to_tuple(const char *list[], size_t count)
{
    size_t total_length = 3;
    size_t i;
    char *tuple;
    char *cursor;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            return NULL;
        }

        len = strnlen(list[i], MAX_STRING_LENGTH);

        if (total_length > SIZE_MAX - (len + 4)) {
            return NULL;
        }

        total_length += len + 2;

        if (i > 0) {
            total_length += 2;
        }
    }

    tuple = (char *)malloc(total_length);
    if (tuple == NULL) {
        return NULL;
    }

    cursor = tuple;
    *cursor++ = '(';

    for (i = 0; i < count; i++) {
        size_t len = strnlen(list[i], MAX_STRING_LENGTH);
        size_t space_left = total_length - (size_t)(cursor - tuple);

        if (i > 0) {
            *cursor++ = ',';
            *cursor++ = ' ';
            space_left -= 2;
        }

        if (space_left < len + 4) {
            free(tuple);
            return NULL;
        }

        *cursor++ = '\'';
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(cursor, list[i], len);
        cursor += len;
        *cursor++ = '\'';
    }

    *cursor++ = ')';
    *cursor = '\0';

    return tuple;
}

int main(void)
{
    const char *fruits[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(fruits) / sizeof(fruits[0]);
    char *result = string_list_to_tuple(fruits, count);

    if (result == NULL) {
        fprintf(stderr, "Error: failed to convert string list to tuple\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}