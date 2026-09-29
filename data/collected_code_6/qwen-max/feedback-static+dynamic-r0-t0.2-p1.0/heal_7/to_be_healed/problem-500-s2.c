#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char *list[], int size) {
    if (size <= 0) return NULL;

    int total_length = 0;
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(list[i]) + 1;
    }

    char *result = (char *)malloc(total_length);
    if (result == NULL) return NULL;

    result[0] = '\0';
    int current_len = 0;
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(list[i]);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + current_len, list[i], len);
        current_len += len;
        result[current_len++] = ' ';
    }
    result[total_length - 2] = '\0';

    return result;
}

int main() {
    const char *list[] = {"Hello", " ", "World", "!"};
    int size = sizeof(list) / sizeof(list[0]);

    char *concatenated = concatenate_list(list, size);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}