#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(const char **words, size_t num_words, size_t n, size_t *out_count);

char **shortlist_words(const char **words, size_t num_words, size_t n, size_t *out_count) {
    if (!words || !out_count) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < num_words; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] && strlen(words[i]) > n) {
            count++;
        }
    }

    if (count == 0) {
        *out_count = 0;
        return NULL;
    }

    char **result = malloc(count * sizeof(char *));
    if (!result) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < num_words; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] && strlen(words[i]) > n) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]);
            result[index] = malloc(len + 1);
            if (!result[index]) {
                for (size_t j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result[index], words[i]);
            index++;
        }
    }

    *out_count = count;
    return result;
}

int main(void) {
    const char *input_words[] = {"apple", "cat", "banana", "dog", "elephant", "fox"};
    size_t num_words = sizeof(input_words) / sizeof(input_words[0]);
    size_t n = 3;
    size_t out_count = 0;

    char **filtered = shortlist_words(input_words, num_words, n, &out_count);

    if (filtered) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s\n", filtered[i]);
            free(filtered[i]);
        }
        free(filtered);
    }

    return 0;
}