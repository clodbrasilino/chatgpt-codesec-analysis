#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* replace_multiple_occurrences(const char* str, char ch) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i, j = 0;
    int in_sequence = 0;

    for (i = 0; i < len; i++) {
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
    char ch = 'a';

    char* output = replace_multiple_occurrences(input, ch);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Modified: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}