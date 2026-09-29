#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 4096

char **remove_duplicates(const char **words, size_t count, size_t *out_count)
{
    char **result = NULL;
    size_t unique = 0;
    size_t i;
    size_t j;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (words == NULL || count == 0) {
        return NULL;
    }

    result = calloc(count, sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        int found = 0;
        size_t len;

        if (words[i] == NULL) {
            continue;
        }

        len = strnlen(words[i], MAX_WORD_LEN);
        if (len >= MAX_WORD_LEN) {
            continue;
        }

        for (j = 0; j < unique; j++) {
            if (strcmp(result[j], words[i]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result[unique] = malloc(len + 1);
            if (result[unique] == NULL) {
                for (j = 0; j < unique; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(result[unique], words[i], len);
            result[unique][len] = '\0';
            unique++;
        }
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
        "apple", "banana", "apple", "cherry", "banana", "date", "apple"
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

    printf("Unique words:\n");
    for (i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
    }

    free_word_list(result, result_count);

    return EXIT_SUCCESS;
}