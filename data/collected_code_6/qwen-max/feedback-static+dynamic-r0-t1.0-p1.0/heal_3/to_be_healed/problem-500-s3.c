#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenate_list(const char **list, int count) {
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(list[i]) + 1;
    }
    char *result = malloc(total_len);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    size_t pos = 0;
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(list[i]);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + pos, list[i], len);
        pos += len;
        result[pos] = '\0';
        if (i < count - 1) {
            result[pos++] = ' ';
        }
    }
    return result;
}

int main() {
    const char *words[] = {"Hello", "world", "this", "is", "C"};
    int count = sizeof(words) / sizeof(words[0]);
    char *concatenated = concatenate_list(words, count);
    if (concatenated != NULL) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    return 0;
}