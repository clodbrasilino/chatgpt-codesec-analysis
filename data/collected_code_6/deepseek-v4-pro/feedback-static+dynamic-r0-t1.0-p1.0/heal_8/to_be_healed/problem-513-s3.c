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
    if (str_len == SIZE_MAX) {
        return NULL;
    }

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
        if (tuple_len == SIZE_MAX) {
            free_list(list, size);
            return NULL;
        }

        if (tuple_len >= SIZE_MAX - 1) {
            free_list(list, size);
            return NULL;
        }

        /* Possible weaknesses found:
         *  alloc_size is assigned 'tuple_len+1' here.
         *  Assignment 'alloc_size=tuple_len+1', assigned value is greater than 0
         */
        size_t alloc_size = tuple_len + 1;
        /* Possible weaknesses found:
         *  Condition 'alloc_size<tuple_len' is always false
         *  Condition 'alloc_size==0' is always false [knownConditionTrueFalse]
         *  Condition 'alloc_size==0' is always false
         *  Condition 'alloc_size<tuple_len' is always false [knownConditionTrueFalse]
         */
        if (alloc_size == 0 || alloc_size < tuple_len) {
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
        memcpy(list[i * 2], tuple[i], tuple_len);
        list[i * 2][tuple_len] = '\0';

        /* Possible weaknesses found:
         *  Assignment 'str_alloc_size=str_len+1', assigned value is greater than 0
         *  str_alloc_size is assigned 'str_len+1' here.
         */
        size_t str_alloc_size = str_len + 1;
        /* Possible weaknesses found:
         *  Condition 'str_alloc_size==0' is always false [knownConditionTrueFalse]
         *  Condition 'str_alloc_size<str_len' is always false [knownConditionTrueFalse]
         *  Condition 'str_alloc_size<str_len' is always false
         *  Condition 'str_alloc_size==0' is always false
         */
        if (str_alloc_size == 0 || str_alloc_size < str_len) {
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
        memcpy(list[i * 2 + 1], str, str_len);
        list[i * 2 + 1][str_len] = '\0';
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