#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *concatenate_list(char **list, int size) {
    if (list == NULL || size <= 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] == NULL) {
            return NULL;
        }
        size_t len = strnlen(list[i], SIZE_MAX - total_length);
        if (len >= SIZE_MAX - total_length) {
            return NULL;
        }
        total_length += len;
    }

    if (total_length >= SIZE_MAX) {
        return NULL;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(list[i]);
        if (offset + len > total_length) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + offset, list[i], len);
        offset += len;
    }
    result[offset] = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char *result = concatenate_list(list, size);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate list\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}