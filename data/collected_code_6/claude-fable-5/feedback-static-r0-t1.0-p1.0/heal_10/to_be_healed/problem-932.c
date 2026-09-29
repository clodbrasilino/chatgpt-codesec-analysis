#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_WORD_LEN 4096

char **remove_duplicates(const char *const *words, size_t count, size_t *out_count);
void free_word_list(char **words, size_t count);

char **remove_duplicates(const char *const *words, size_t count, size_t *out_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t unique;

    if (words == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (count == 0) {
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    result = malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    unique = 0;
    for (i = 0; i < count; i++) {
        int found = 0;
        size_t len;
        size_t alloc_size;

        if (words[i] == NULL) {
            continue;
        }

        len = strnlen(words[i], MAX_WORD_LEN);
        if (len >= MAX_WORD_LEN) {
            continue;
        }

        for (j = 0; j < unique; j++) {
            if (strncmp(result[j], words[i], MAX_WORD_LEN) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            continue;
        }

        if (len > SIZE_MAX - 1) {
            continue;
        }
        alloc_size = len + 1;

        result[unique] = malloc(alloc_size);
        if (result[unique] == NULL) {
            for (j = 0; j < unique; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[unique], words[i], len);
        result[unique][len] = '\0';
        unique++;
    }

    *out_count = unique;
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
    const char *input[] = {
        "apple", "banana", "apple", "cherry", "banana", "date", "cherry"
    };
    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t result_count = 0;
    char **result;
    size_t i;

    result = remove_duplicates(input, input_count, &result_count);
    if (result == NULL) {
        fprintf(stderr, "Failed to remove duplicates\n");
        return EXIT_FAILURE;
    }

    printf("Original list:\n");
    for (i = 0; i < input_count; i++) {
        printf("  %s\n", input[i]);
    }

    printf("Deduplicated list:\n");
    for (i = 0; i < result_count; i++) {
        printf("  %s\n", result[i]);
    }

    free_word_list(result, result_count);

    return EXIT_SUCCESS;
}