#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *remove_whitespace(const char *input);

char *remove_whitespace(const char *input)
{
    char *result = NULL;
    size_t result_len = 0;
    size_t input_len;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (!isspace(c)) {
            result[result_len++] = (char)c;
        }
    }

    result[result_len] = '\0';
    return result;
}

int main(void)
{
    char *input = NULL;
    char *cleaned = NULL;

    input = malloc(MAX_INPUT_LEN);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[MAX_INPUT_LEN - 1] = '\0';

    cleaned = remove_whitespace(input);
    free(input);

    if (cleaned == NULL) {
        fprintf(stderr, "Failed to remove whitespace\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", cleaned) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    free(cleaned);
    return EXIT_SUCCESS;
}