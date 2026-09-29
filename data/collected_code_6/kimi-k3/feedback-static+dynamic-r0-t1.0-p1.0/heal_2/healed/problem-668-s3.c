#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* replace_multiple_occurrences(const char* str, size_t str_len, char ch) {
    if (str == NULL) {
        return NULL;
    }

    char* result = (char*)malloc(str_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i, j = 0;
    int in_sequence = 0;

    for (i = 0; i < str_len; i++) {
        if (str[i] == ch) {
            if (!in_sequence) {
                result[j++] = ch;
                in_sequence = 1;
            }
        } else {
            result[j++] = str[i];
            in_sequence = 0;
        }
    }
    result[j] = '\0';

    return result;
}

int main() {
    const char* input = "aaabbbcccdaa";
    size_t input_len = strnlen(input, 256);
    char ch = 'a';

    char* output = replace_multiple_occurrences(input, input_len, ch);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Modified: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}