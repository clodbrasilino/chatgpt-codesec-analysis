#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_duplicates(const char *const *words, size_t count, size_t *out_count)
{
    char **result = NULL;
    size_t result_count = 0;
    size_t i;
    size_t j;

    if (words == NULL || out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        int found = 0;

        if (words[i] == NULL) {
            continue;
        }

        for (j = 0; j < result_count; j++) {
            if (strcmp(result[j], words[i]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]) + 1;
            char *copy = malloc(len);

            if (copy == NULL) {
                for (j = 0; j < result_count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(copy, words[i], len);
            result[result_count] = copy;
            result_count++;
        }
    }

    *out_count = result_count;
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
    const char *words[] = {
        "apple", "banana", "apple", "cherry", "banana", "date", "cherry"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t unique_count = 0;
    char **unique_words;
    size_t i;

    unique_words = remove_duplicates(words, count, &unique_count);
    if (unique_words == NULL) {
        fprintf(stderr, "Failed to remove duplicates\n");
        return EXIT_FAILURE;
    }

    printf("Unique words:\n");
    for (i = 0; i < unique_count; i++) {
        printf("%s\n", unique_words[i]);
    }

    free_word_list(unique_words, unique_count);

    return EXIT_SUCCESS;
}