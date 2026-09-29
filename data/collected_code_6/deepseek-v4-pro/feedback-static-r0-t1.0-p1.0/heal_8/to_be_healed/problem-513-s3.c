#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

static size_t safe_strlen(const char* str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < MAX_STRING_LENGTH && str[len] != '\0') {
        len++;
    }
    if (str[len] != '\0') {
        return 0;
    }
    return len;
}

char** tuple_to_list(char** tuple, int size, const char* str) {
    if (tuple == NULL || str == NULL || size <= 0) {
        return NULL;
    }

    size_t str_len = safe_strlen(str);
    if (str_len == 0 || str_len >= MAX_STRING_LENGTH) {
        return NULL;
    }

    char** list = (char**)calloc((size_t)(size * 2), sizeof(char*));
    if (list == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            for (int j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        size_t tuple_len = safe_strlen(tuple[i]);
        /* Possible weaknesses found:
         *  Assuming that condition 'tuple_len==0' is not redundant
         */
        if (tuple_len == 0 || tuple_len >= MAX_STRING_LENGTH) {
            for (int j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }

        list[i * 2] = (char*)malloc(tuple_len + 1);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (list[i * 2] == NULL) {
            for (int j = 0; j < i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Condition 'tuple_len>0' is always true [knownConditionTrueFalse]
         *  Condition 'tuple_len>0' is always true
         */
        if (tuple_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(list[i * 2], tuple[i], tuple_len);
        }
        list[i * 2][tuple_len] = '\0';

        list[i * 2 + 1] = (char*)malloc(str_len + 1);
        if (list[i * 2 + 1] == NULL) {
            for (int j = 0; j <= i * 2; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        if (str_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(list[i * 2 + 1], str, str_len);
        }
        list[i * 2 + 1][str_len] = '\0';
    }

    return list;
}

void free_list(char** list, int size) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < size * 2; i++) {
        free(list[i]);
    }
    free(list);
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