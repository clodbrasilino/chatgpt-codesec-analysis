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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    char *cleaned;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    cleaned = remove_whitespace(input);
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