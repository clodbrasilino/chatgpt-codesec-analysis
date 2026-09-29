#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

char *sort_string(const char *str) {
    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }
    char *sorted = malloc(len + 1);
    if (!sorted) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, str, len + 1);
    qsort(sorted, len, sizeof(char), compare_chars);
    return sorted;
}

char **find_anagrams(const char *target, char **list, size_t list_size, size_t *result_size) {
    *result_size = 0;
    if (!target || !list || list_size == 0) {
        return NULL;
    }

    char **result = malloc(list_size * sizeof(char *));
    if (!result) {
        return NULL;
    }

    size_t target_len = strnlen(target, SIZE_MAX);
    if (target_len == SIZE_MAX) {
        free(result);
        return NULL;
    }

    char *sorted_target = sort_string(target);
    if (!sorted_target) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < list_size; i++) {
        if (!list[i]) {
            continue;
        }

        if (strnlen(list[i], SIZE_MAX) != target_len) {
            continue;
        }

        char *sorted_word = sort_string(list[i]);
        if (!sorted_word) {
            free(sorted_target);
            for (size_t j = 0; j < *result_size; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        if (strcmp(sorted_target, sorted_word) == 0) {
            size_t word_len = strnlen(list[i], target_len);
            result[*result_size] = malloc(word_len + 1);
            if (!result[*result_size]) {
                free(sorted_word);
                free(sorted_target);
                for (size_t j = 0; j < *result_size; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*result_size], list[i], word_len);
            result[*result_size][word_len] = '\0';
            (*result_size)++;
        }
        free(sorted_word);
    }

    free(sorted_target);

    char **shrunk_result = realloc(result, (*result_size) * sizeof(char *));
    if (shrunk_result || *result_size == 0) {
        return shrunk_result;
    }
    
    return result;
}

void free_anagrams(char **anagrams, size_t size) {
    if (!anagrams) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(anagrams[i]);
    }
    free(anagrams);
}

int main(void) {
    const char *target = "listen";
    char *list[] = {"enlist", "google", "inlets", "banana", "silent", "tinsel"};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t result_size = 0;

    char **anagrams = find_anagrams(target, list, list_size, &result_size);

    if (!anagrams) {
        if (result_size == 0) {
            printf("No anagrams found or empty list.\n");
        } else {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
    } else {
        printf("Anagrams of '%s':\n", target);
        for (size_t i = 0; i < result_size; i++) {
            printf("%s\n", anagrams[i]);
        }
        free_anagrams(anagrams, result_size);
    }

    return 0;
}