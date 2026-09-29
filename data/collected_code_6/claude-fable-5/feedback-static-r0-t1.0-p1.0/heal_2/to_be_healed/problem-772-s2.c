#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096U

char *remove_words_of_length_k(const char *input, size_t k)
{
    char *result;
    size_t len;
    size_t i;
    size_t out;
    size_t start;
    size_t word_len;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LENGTH);
    if (len >= MAX_INPUT_LENGTH) {
        return NULL;
    }

    result = (char *)malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    i = 0U;
    out = 0U;

    while (i <= len) {
        if ((input[i] == ' ') || (input[i] == '\0')) {
            i++;
            continue;
        }

        start = i;
        while ((i < len) && (input[i] != ' ') && (input[i] != '\0')) {
            i++;
        }
        word_len = i - start;

        if (word_len != k) {
            if (out > 0U) {
                if (out >= len) {
                    free(result);
                    return NULL;
                }
                result[out] = ' ';
                out++;
            }
            if ((out + word_len) > len) {
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            (void)memcpy(&result[out], &input[start], word_len);
            out += word_len;
        }
    }

    result[out] = '\0';
    return result;
}

int main(void)
{
    const char *text = "the quick brown fox jumps over a lazy dog";
    size_t k = 3U;
    char *filtered;

    filtered = remove_words_of_length_k(text, k);
    if (filtered == NULL) {
        (void)fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", text) < 0) {
        free(filtered);
        return EXIT_FAILURE;
    }

    if (printf("Filtered: %s\n", filtered) < 0) {
        free(filtered);
        return EXIT_FAILURE;
    }

    free(filtered);
    return EXIT_SUCCESS;
}