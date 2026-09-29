#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_elements(char **list, int length) {
    if (length <= 0) return NULL;

    size_t total_length = 0;
    for (int i = 0; i < length; ++i) {
        size_t len = strnlen(list[i], 4096);
        if (len == 4096) return NULL;
        total_length += len;
        if (i < length - 1) total_length++;
    }

    char *result = malloc(total_length + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    char *current_pos = result;
    for (int i = 0; i < length; ++i) {
        size_t len = strnlen(list[i], 4096);
        if (len == 4096) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(current_pos, list[i], len);
        current_pos[len] = '\0';
        current_pos += len;
        if (i < length - 1) {
            *current_pos++ = ' ';
        }
    }

    return result;
}

int main() {
    char *elements[] = {"Hello", "", "World", ""};
    int num_elements = 4;

    char *concatenated = concatenate_elements(elements, num_elements);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed or string too long\n");
    }

    return 0;
}