#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return NULL;
    }

    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    size_t input_len = strnlen(input, 256);
    char *output = remove_odd_index_chars(input, input_len);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
        output = NULL;
    }

    const char *test_str = "test";
    size_t test_len = strnlen(test_str, 256);
    char *test_output = remove_odd_index_chars(test_str, test_len);
    if (test_output != NULL) {
        printf("%s\n", test_output);
        free(test_output);
    }

    char *null_test = remove_odd_index_chars(NULL, 0);
    if (null_test == NULL) {
        printf("NULL test handled correctly.\n");
    }

    return 0;
}