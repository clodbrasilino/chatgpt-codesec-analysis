#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        if (list[i] == NULL) {
            return NULL;
        }
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
        size_t len;
        if (i > 0) {
            *cursor++ = ',';
            *cursor++ = ' ';
        }
        *cursor++ = '\'';
        len = strlen(list[i]);
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