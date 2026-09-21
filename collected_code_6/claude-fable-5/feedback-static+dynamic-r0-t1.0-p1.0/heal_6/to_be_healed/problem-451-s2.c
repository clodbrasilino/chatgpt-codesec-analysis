#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *remove_whitespace(const char *input);
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'iOSSwift', got <no output>
  *  test case 1 failed: expected 'GoogleDart', got <no output>
  *  test case 0 failed: expected 'GoogleFlutter', got <no output>
  */

char *remove_whitespace(const char *input)
{
    char *result = NULL;
    size_t result_len = 0;
    size_t input_len = 0;
    size_t buffer_size;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    while (input_len < MAX_INPUT_LEN && input[input_len] != '\0') {
        input_len++;
    }

    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    buffer_size = input_len + 1;
    result = malloc(buffer_size);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];
        if (!isspace(c)) {
            if (result_len >= buffer_size - 1) {
                free(result);
                return NULL;
            }
            result[result_len] = (char)c;
            result_len++;
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