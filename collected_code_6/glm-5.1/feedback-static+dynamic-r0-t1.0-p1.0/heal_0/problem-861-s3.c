#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

char *sort_string(const char *str) {
    size_t len = strlen(str);
    char *sorted = malloc(len + 1);
    if (!sorted) {
        return NULL;
    }
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

    char *sorted_target = sort_string(target);
    if (!sorted_target) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < list_size; i++) {
        if (!list[i]) {
            continue;
        }

        if (strlen(list[i]) != strlen(target)) {
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
            size_t word_len = strlen(list[i]);
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
            memcpy(result[*result_size], list[i], word_len + 1);
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