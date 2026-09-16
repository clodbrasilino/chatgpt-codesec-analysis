#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(const char *const *words, size_t count, size_t n, size_t *result_count)
{
    char **result = NULL;
    size_t matched = 0;
    size_t i;

    if (words == NULL || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            matched++;
        }
    }

    *result_count = 0;

    if (matched == 0) {
        return NULL;
    }

    result = malloc(matched * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            size_t len = strlen(words[i]);
            char *copy = malloc(len + 1);
            if (copy == NULL) {
                size_t j;
                for (j = 0; j < *result_count; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            memcpy(copy, words[i], len + 1);
            result[*result_count] = copy;
            (*result_count)++;
        }
    }

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
    const char *const words[] = {
        "apple", "cat", "banana", "dog", "elephant", "sun", "computer"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t n = 4;
    size_t result_count = 0;
    char **shortlisted;
    size_t i;

    shortlisted = shortlist_words(words, word_count, n, &result_count);

    if (shortlisted == NULL) {
        if (printf("No words longer than %zu found.\n", n) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Words longer than %zu characters:\n", n) < 0) {
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