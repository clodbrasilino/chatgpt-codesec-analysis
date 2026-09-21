#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LENGTH 64

int is_word_in_array(const char *word, const char *words[], int num_words) {
    for (int i = 0; i < num_words; ++i) {
        if (strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

char *remove_duplicate_words(const char *input) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_length = strlen(input);
    char *result = (char *)malloc(input_length + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *words[MAX_WORDS];
    int num_words = 0;

    const char *p = input;

    while (*p) {
        while (*p && !isalnum((unsigned char)*p)) p++;
        const char *word_start = p;
        while (*p && isalnum((unsigned char)*p)) p++;

        if (word_start != p && !is_word_in_array(word_start, (const char *const *)words, num_words)) {
            if (num_words >= MAX_WORDS) {
                free(result);
                return NULL;
            }
            words[num_words++] = word_start;
            size_t word_length = p - word_start;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t result_length = strlen(result);

            if (result_length + word_length + 1 > input_length + 1) {
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, word_start, word_length);
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant character. (risk 1, buffer)
             */
            strncat(result, " ", 1);
        }

        while (*p && !isalnum((unsigned char)*p)) p++;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    result[strlen(result) - 1] = '\0';

    return result;
}

int main() {
    const char *input = "this this is a test test of a duplicate remover";
    char *output = remove_duplicate_words(input);

    if (output == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or too many unique words.\n");
        return 1;
    }

    printf("Original: %s\n", input);
    printf("Processed: %s\n", output);

    free(output);
    return 0;
}