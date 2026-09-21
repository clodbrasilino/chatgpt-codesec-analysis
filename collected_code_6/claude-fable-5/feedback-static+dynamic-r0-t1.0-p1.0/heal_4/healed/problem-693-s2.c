#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096U

char *remove_multiple_spaces(const char *input);

char *remove_multiple_spaces(const char *input)
{
    char *output;
    size_t len;
    size_t i;
    size_t j;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    output = malloc(len + 1U);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        if (input[i] == ' ' && j > 0U && output[j - 1U] == ' ') {
            continue;
        }
        output[j] = input[i];
        j++;
    }
    output[j] = '\0';

    return output;
}

int main(void)
{
    char input[MAX_INPUT_LEN];
    char *result;
    size_t len;

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    }

    result = remove_multiple_spaces(input);
    if (result == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}