#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    size_t alloc_size = len / 2 + 2;
    if (alloc_size == 0) {
        return NULL;
    }

    char *result = malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    size_t input_len = strlen(input);
    char *output = remove_odd_index_chars(input, input_len);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    char *null_test = remove_odd_index_chars(NULL, 0);
    if (null_test == NULL) {
        printf("NULL input handled correctly.\n");
    } else {
        free(null_test);
    }

    return 0;
}