#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

static char *remove_uppercase(const char *input)
{
    char *result;
    size_t input_len;
    size_t result_pos;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input exceeds maximum allowed length\n");
        return NULL;
    }

    result = calloc(input_len + 1, sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    result_pos = 0;
    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (!isupper(c)) {
            if (result_pos >= input_len) {
                fprintf(stderr, "Internal bounds error\n");
                free(result);
                return NULL;
            }
            result[result_pos] = (char)c;
            result_pos++;
        }
    }

    result[result_pos] = '\0';
    return result;
}

int main(void)
{
    char *buffer;
    char *cleaned;
    size_t len;

    buffer = calloc(MAX_INPUT_LEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_INPUT_LEN - 1] = '\0';
    len = strnlen(buffer, MAX_INPUT_LEN);
    while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
        buffer[len - 1] = '\0';
        len--;
    }

    cleaned = remove_uppercase(buffer);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);

    free(cleaned);
    free(buffer);

    return EXIT_SUCCESS;
}