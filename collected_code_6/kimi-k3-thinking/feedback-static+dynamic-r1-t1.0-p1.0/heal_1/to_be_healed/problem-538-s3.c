#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_list_to_tuple(const char *list[], size_t count)
{
    size_t total_length = 3;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;
    char *tuple;
    char *cursor;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(list[i]) + 2;
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
        if (i > 0) {
            *cursor++ = ',';
            *cursor++ = ' ';
        }
        *cursor++ = '\'';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len = strlen(list[i]);
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