#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(const char *const *words, size_t count, size_t n, size_t *result_count)
{
    char **result;
    size_t matched;
    size_t i;

    if (result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    if (words == NULL || count == 0) {
        return NULL;
    }

    matched = 0;
    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] != NULL && strlen(words[i]) > n) {
            matched++;
        }
    }

    if (matched == 0) {
        return NULL;
    }

    result = malloc(matched * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    matched = 0;
    for (i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (words[i] != NULL && strlen(words[i]) > n) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]);
            char *copy = malloc(len + 1);
            if (copy == NULL) {
                size_t j;
                for (j = 0; j < matched; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(copy, words[i], len + 1);
            result[matched] = copy;
            matched++;
        }
    }

    *result_count = matched;
    return result;
}

void free_shortlist(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    const char *words[] = { "apple", "cat", "banana", "dog", "elephant", "sun" };
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t n = 3;
    size_t result_count = 0;
    size_t i;
    char **shortlisted;

    shortlisted = shortlist_words(words, count, n, &result_count);

    if (shortlisted == NULL) {
        if (printf("No words longer than %zu found.\n", n) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Words longer than %zu:\n", n) < 0) {
        free_shortlist(shortlisted, result_count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        if (printf("%s\n", shortlisted[i]) < 0) {
            free_shortlist(shortlisted, result_count);
            return EXIT_FAILURE;
        }
    }

    free_shortlist(shortlisted, result_count);
    return EXIT_SUCCESS;
}