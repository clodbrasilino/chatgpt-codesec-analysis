#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 4096

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count);
void free_word_list(char **list, size_t count);

char **remove_words(char **words, size_t count, char **targets, size_t target_count, size_t *new_count)
{
    char **result;
    size_t i;
    size_t j;
    size_t kept;
    int match;

    if (words == NULL || new_count == NULL) {
        return NULL;
    }

    result = malloc(sizeof(char *) * (count > 0 ? count : 1));
    if (result == NULL) {
        return NULL;
    }

    kept = 0;
    for (i = 0; i < count; i++) {
        size_t word_len;

        if (words[i] == NULL) {
            continue;
        }

        word_len = strnlen(words[i], MAX_WORD_LEN);
        if (word_len >= MAX_WORD_LEN) {
            while (kept > 0) {
                kept--;
                free(result[kept]);
            }
            free(result);
            return NULL;
        }

        match = 0;
        for (j = 0; j < target_count; j++) {
            if (targets != NULL && targets[j] != NULL &&
                strnlen(targets[j], MAX_WORD_LEN) < MAX_WORD_LEN &&
                strcmp(words[i], targets[j]) == 0) {
                match = 1;
                break;
            }
        }

        if (match == 0) {
            size_t alloc_len = word_len + 1;

            result[kept] = malloc(alloc_len);
            if (result[kept] == NULL) {
                while (kept > 0) {
                    kept--;
                    free(result[kept]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[kept], words[i], word_len);
            result[kept][word_len] = '\0';
            kept++;
        }
    }

    *new_count = kept;
    return result;
}

void free_word_list(char **list, size_t count)
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
    char *words[] = { "apple", "banana", "cherry", "date", "banana", "fig" };
    char *targets[] = { "banana", "date" };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t target_count = sizeof(targets) / sizeof(targets[0]);
    size_t new_count = 0;
    size_t i;
    char **filtered;

    filtered = remove_words(words, word_count, targets, target_count, &new_count);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to remove words\n");
        return EXIT_FAILURE;
    }

    printf("Remaining words:\n");
    for (i = 0; i < new_count; i++) {
        printf("%s\n", filtered[i]);
    }

    free_word_list(filtered, new_count);
    return EXIT_SUCCESS;
}