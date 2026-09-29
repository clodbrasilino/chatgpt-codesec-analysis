#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);

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
        while ((input[i] != ' ') && (input[i] != '\0')) {
            i++;
        }
        word_len = i - start;

        if (word_len != k) {
            if (out > 0U) {
                result[out] = ' ';
                out++;
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