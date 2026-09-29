#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespace(const char *input) {
    char *result;
    size_t input_len;
    size_t result_len = 0;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, 1024);
    if (input_len == 1024 && input[input_len] != '\0') {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        if (!isspace((unsigned char)input[i])) {
            result[result_len] = input[i];
            result_len++;
        }
    }

    result[result_len] = '\0';

    return result;
}

int main(void) {
    const char *test_string = "Hello World \t This is a test \n string";
    char *cleaned;

    cleaned = remove_whitespace(test_string);
    if (cleaned == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}