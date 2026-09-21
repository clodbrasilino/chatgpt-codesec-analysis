#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_words_of_length(const char *str, size_t k)
{
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t out = 0;
    int separator_needed = 0;

    while (str[i] != '\0') {
        while (str[i] != '\0' && isspace((unsigned char)str[i])) {
            i++;
        }
        if (str[i] == '\0') {
            break;
        }

        size_t start = i;
        while (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_len = i - start;

        if (word_len != k) {
            if (separator_needed) {
                result[out++] = ' ';
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out, str + start, word_len);
            out += word_len;
            separator_needed = 1;
        }
    }
    result[out] = '\0';

    return result;
}

int main(void)
{
    const char *input = "The quick brown fox jumps over the lazy dog";
    size_t k = 3;

    char *modified = remove_words_of_length(input, k);
    if (modified == NULL) {
        fprintf(stderr, "Error: unable to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("Original string: %s\n", input);
    printf("After removing words of length %zu: %s\n", k, modified);

    free(modified);
    modified = NULL;

    return EXIT_SUCCESS;
}