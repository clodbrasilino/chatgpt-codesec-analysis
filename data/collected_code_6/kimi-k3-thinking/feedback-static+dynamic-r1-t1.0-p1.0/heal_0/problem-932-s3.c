#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **remove_duplicate_words(const char *const *words, size_t count, size_t *result_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t len;
    size_t unique_count = 0;
    int is_duplicate;

    if (result_count == NULL) {
        return NULL;
    }
    *result_count = 0;

    if (words == NULL || count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        is_duplicate = 0;
        for (j = 0; j < unique_count; j++) {
            if (strcmp(result[j], words[i]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            len = strlen(words[i]) + 1;
            result[unique_count] = malloc(len);
            if (result[unique_count] == NULL) {
                for (j = 0; j < unique_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[unique_count], words[i], len);
            unique_count++;
        }
    }

    *result_count = unique_count;
    return result;
}

void free_word_list(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void)
{
    const char *words[] = {"apple", "banana", "apple", "cherry", "banana", "date", "cherry"};
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t result_count = 0;
    size_t i;
    char **unique_words;

    unique_words = remove_duplicate_words(words, count, &result_count);
    if (unique_words == NULL) {
        fprintf(stderr, "Error: failed to process word list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; i++) {
        printf("%s\n", unique_words[i]);
    }

    free_word_list(unique_words, result_count);

    return EXIT_SUCCESS;
}