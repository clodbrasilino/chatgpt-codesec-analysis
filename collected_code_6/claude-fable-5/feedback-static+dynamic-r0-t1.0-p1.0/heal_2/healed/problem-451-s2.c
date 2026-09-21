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
    size_t buffer_size;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
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
    const char *test = "  Hello \t World \n from  C  ";
    char *cleaned;

    cleaned = remove_whitespace(test);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to remove whitespace\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: \"%s\"\n", test) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    if (printf("Cleaned:  \"%s\"\n", cleaned) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    free(cleaned);
    return EXIT_SUCCESS;
}