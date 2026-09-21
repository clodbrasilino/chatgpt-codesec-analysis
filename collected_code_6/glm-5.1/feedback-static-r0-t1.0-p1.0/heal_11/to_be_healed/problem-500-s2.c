#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, size_t size) {
    size_t total_length = 0;
    size_t i;
    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (total_length > SIZE_MAX - len) {
                return NULL;
            }
            total_length += len;
        }
    }

    if (total_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    size_t current_pos = 0;
    for (i = 0; i < size; i++) {
        if (list[i] != NULL) {
            size_t len = strnlen(list[i], SIZE_MAX);
            if (current_pos > SIZE_MAX - len) {
                free(result);
                return NULL;
            }
            size_t next_pos = current_pos + len;
            if (next_pos > total_length) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + current_pos, list[i], len);
            current_pos = next_pos;
        }
    }
    result[current_pos] = '\0';

    return result;
}

int main(void) {
    char *list[] = {"Hello", ", ", "world", "!"};
    size_t size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", concatenated);
    free(concatenated);
    concatenated = NULL;

    return EXIT_SUCCESS;
}