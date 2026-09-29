#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WordCount {
    char *word;
    size_t count;
};

static char *findSecondMostFrequent(const char **words, size_t n)
{
    struct WordCount *table = NULL;
    size_t tableSize = 0;
    size_t i;
    size_t j;
    char *result = NULL;

    if (words == NULL || n < 2) {
        return NULL;
    }

    table = calloc(n, sizeof(struct WordCount));
    if (table == NULL) {
        return NULL;
    }

    for (i = 0; i < n; i++) {
        int found = 0;

        if (words[i] == NULL) {
            continue;
        }

        for (j = 0; j < tableSize; j++) {
            if (strcmp(table[j].word, words[i]) == 0) {
                table[j].count++;
                found = 1;
                break;
            }
        }

        if (found == 0) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]) + 1;
            char *copy = malloc(len);

            if (copy == NULL) {
                for (j = 0; j < tableSize; j++) {
                    free(table[j].word);
                }
                free(table);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(copy, words[i], len);
            table[tableSize].word = copy;
            table[tableSize].count = 1;
            tableSize++;
        }
    }

    if (tableSize >= 2) {
        size_t firstIdx = 0;
        size_t secondIdx = tableSize;

        for (j = 1; j < tableSize; j++) {
            if (table[j].count > table[firstIdx].count) {
                secondIdx = firstIdx;
                firstIdx = j;
            } else if (secondIdx == tableSize ||
                       table[j].count > table[secondIdx].count) {
                secondIdx = j;
            }
        }

        if (secondIdx < tableSize) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(table[secondIdx].word) + 1;

            result = malloc(len);
            if (result != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, table[secondIdx].word, len);
            }
        }
    }

    for (j = 0; j < tableSize; j++) {
        free(table[j].word);
    }
    free(table);

    return result;
}

int main(void)
{
    const char *sequence[] = {
        "apple", "banana", "apple", "orange",
        "banana", "apple", "orange", "banana", "banana"
    };
    size_t count = sizeof(sequence) / sizeof(sequence[0]);
    char *second = NULL;

    second = findSecondMostFrequent(sequence, count);
    if (second == NULL) {
        fprintf(stderr, "Could not determine the second most frequent string\n");
        return EXIT_FAILURE;
    }

    if (printf("Second most frequent string: %s\n", second) < 0) {
        free(second);
        return EXIT_FAILURE;
    }

    free(second);
    return EXIT_SUCCESS;
}