#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    size_t alloc_size = len / 2 + 1;
    if (alloc_size == 0) {
        return NULL;
    }

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
    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    char *output = remove_odd_index_chars(input, input_len);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    const char *empty_test = remove_odd_index_chars("", 0);
    if (empty_test == NULL) {
        printf("Empty input handled correctly.\n");
    }

    return 0;
}