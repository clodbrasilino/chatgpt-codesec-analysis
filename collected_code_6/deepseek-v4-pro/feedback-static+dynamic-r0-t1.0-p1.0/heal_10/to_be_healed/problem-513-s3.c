#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void free_list(char** list, int size) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < size * 2; i++) {
        free(list[i]);
    }
    free(list);
}

char** tuple_to_list(char** tuple, int size, const char* str) {
    if (tuple == NULL || str == NULL || size <= 0) {
        return NULL;
    }

    size_t str_len = strnlen(str, SIZE_MAX);
    if (str_len >= SIZE_MAX - 1) {
        return NULL;
    }

    char** list = (char**)calloc((size_t)size * 2, sizeof(char*));
    if (list == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            free_list(list, size);
            return NULL;
        }

        size_t tuple_len = strnlen(tuple[i], SIZE_MAX);
        if (tuple_len >= SIZE_MAX - 1) {
            free_list(list, size);
            return NULL;
        }

        /* Possible weaknesses found:
         *  'alloc_size' is assigned value 'tuple_len+1' here.
         */
        size_t alloc_size = tuple_len + 1;
        /* Possible weaknesses found:
         *  The comparison 'alloc_size < tuple_len+1' is always false because 'alloc_size' and 'tuple_len+1' represent the same value.
         *  The comparison 'alloc_size < tuple_len+1' is always false because 'alloc_size' and 'tuple_len+1' represent the same value. [knownConditionTrueFalse]
         */
        if (alloc_size < tuple_len + 1) {
            free_list(list, size);
            return NULL;
        }

        list[i * 2] = (char*)malloc(alloc_size);
        if (list[i * 2] == NULL) {
            free_list(list, size);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list[i * 2], tuple[i], alloc_size);

        /* Possible weaknesses found:
         *  'str_alloc_size' is assigned value 'str_len+1' here.
         */
        size_t str_alloc_size = str_len + 1;
        /* Possible weaknesses found:
         *  The comparison 'str_alloc_size < str_len+1' is always false because 'str_alloc_size' and 'str_len+1' represent the same value.
         *  The comparison 'str_alloc_size < str_len+1' is always false because 'str_alloc_size' and 'str_len+1' represent the same value. [knownConditionTrueFalse]
         */
        if (str_alloc_size < str_len + 1) {
            free_list(list, size);
            return NULL;
        }

        list[i * 2 + 1] = (char*)malloc(str_alloc_size);
        if (list[i * 2 + 1] == NULL) {
            free_list(list, size);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list[i * 2 + 1], str, str_alloc_size);
    }

    return list;
}

int main(void) {
    char* tuple[] = {"apple", "banana", "cherry"};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    const char* str = "-";

    char** list = tuple_to_list(tuple, size, str);
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < size * 2; i++) {
        printf("%s\n", list[i]);
    }

    free_list(list, size);
    return 0;
}