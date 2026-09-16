#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(const char **words, size_t count, size_t n, size_t *result_count)
{
    char **result = NULL;
    size_t found = 0;
    size_t i;

    if (words == NULL || result_count == NULL) {
        return NULL;
    }

    *result_count = 0;

    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            found++;
        }
    }

    if (found == 0) {
        return NULL;
    }

    result = malloc(found * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            size_t len = strlen(words[i]) + 1;
            result[*result_count] = malloc(len);
            if (result[*result_count] == NULL) {
                size_t j;
                for (j = 0; j < *result_count; j++) {
                    free(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            memcpy(result[*result_count], words[i], len);
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
    const char *words[] = { "apple", "cat", "banana", "dog", "elephant", "hi" };
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t n = 3;
    size_t result_count = 0;
    char **result;
    size_t i;

    result = shortlist_words(words, count, n, &result_count);

    if (result == NULL) {
        if (printf("No words longer than %zu found.\n", n) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Words longer than %zu:\n", n) < 0) {
        free_shortlist(result, result_count);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        if (printf("%s\n", result[i]) < 0) {
            free_shortlist(result, result_count);
            return EXIT_FAILURE;
        }
    }

    free_shortlist(result, result_count);

    return EXIT_SUCCESS;
}