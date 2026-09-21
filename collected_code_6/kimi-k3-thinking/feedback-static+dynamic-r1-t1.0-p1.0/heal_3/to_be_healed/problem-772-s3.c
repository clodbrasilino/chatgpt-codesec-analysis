#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 1024

char *remove_words_of_length(const char *str, size_t k, size_t str_max_len)
{
    if (str == NULL || str_max_len == 0) {
        return NULL;
    }

    size_t len = strnlen(str, str_max_len);
    size_t result_capacity = len + 1;
    char *result = (char *)malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int first_word = 1;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        size_t word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_len = i - word_start;

        if (word_len != k) {
            size_t prefix = first_word ? 0u : 1u;
            if (j + prefix + word_len >= result_capacity) {
                free(result);
                return NULL;
            }
            if (!first_word) {
                result[j++] = ' ';
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + j, str + word_start, word_len);
            j += word_len;
            first_word = 0;
        }
    }
    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    size_t k = 0;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t input_len = strnlen(input, sizeof(input));
    if (input_len == sizeof(input) - 1 && input[input_len - 1] != '\n') {
        fprintf(stderr, "Input is too long (maximum %d characters).\n",
                MAX_INPUT_LEN - 2);
        return EXIT_FAILURE;
    }
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    }

    printf("Enter the word length to remove: ");
    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid length value.\n");
        return EXIT_FAILURE;
    }

    char *modified = remove_words_of_length(input, k, sizeof(input));
    if (modified == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", modified);

    free(modified);
    return EXIT_SUCCESS;
}