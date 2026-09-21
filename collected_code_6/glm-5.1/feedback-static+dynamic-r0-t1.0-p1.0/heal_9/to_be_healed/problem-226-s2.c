#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    if (len == SIZE_MAX) {
        return NULL;
    }

    size_t alloc_size = len / 2 + 1;
    char *result = malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        if (str[i] == '\0') {
            break;
        }
        result[j++] = str[i];
    }
    result[j] = '\0';

    char *trimmed = realloc(result, j + 1);
    if (trimmed != NULL) {
        result = trimmed;
    }

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);

    char *output = remove_odd_index_chars(input, input_len);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    const char *empty_test = remove_odd_index_chars("", 0);
    if (empty_test == NULL) {
        printf("Empty input handled correctly.\n");
    }

    const char *max_test = remove_odd_index_chars("a", SIZE_MAX);
    if (max_test == NULL) {
        printf("SIZE_MAX input handled correctly.\n");
    }

    return 0;
}