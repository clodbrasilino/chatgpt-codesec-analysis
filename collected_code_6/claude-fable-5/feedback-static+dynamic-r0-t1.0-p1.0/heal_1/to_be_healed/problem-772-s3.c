#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_k_length_words(const char *str, size_t k)
{
    char *result;
    size_t len;
    size_t i;
    size_t pos;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    i = 0U;
    pos = 0U;
    while (i < len) {
        if (str[i] == ' ') {
            i++;
            continue;
        }

        size_t start = i;
        while ((i < len) && (str[i] != ' ')) {
            i++;
        }

        size_t word_len = i - start;
        if (word_len != k) {
            if (pos > 0U) {
                result[pos] = ' ';
                pos++;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(&result[pos], &str[start], word_len);
            pos += word_len;
        }
    }

    result[pos] = '\0';
    return result;
}

int main(void)
{
    const char input[] = "the quick brown fox jumps over a lazy dog";
    size_t k = 3U;
    char *output;

    output = remove_k_length_words(input, k);
    if (output == NULL) {
        (void)fprintf(stderr, "Error: memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", input) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    if (printf("Result:   %s\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}