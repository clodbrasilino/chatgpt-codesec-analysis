#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordCount;

int compare(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

char *strdup(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    char *result = malloc(len + 1);
    if (result) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, s, len);
        result[len] = '\0';
    }
    return result;
}

int findMostCommonWords(char *text, int n, WordCount **result) {
    char *p = text;
    WordCount *counts = NULL;
    int count = 0;

    while (*p) {
        while (isspace((unsigned char)*p)) p++;
        char *token = strtok(p, " \t\n.,;:!?");
        if (token == NULL) break;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        p += strlen(token);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(counts[i].word, token) == 0) {
                counts[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            WordCount *newCounts = realloc(counts, (count + 1) * sizeof(WordCount));
            if (newCounts == NULL) {
                for (int i = 0; i < count; i++) {
                    free(counts[i].word);
                }
                free(counts);
                return 0;
            }
            counts = newCounts;
            counts[count].word = strdup(token);
            if (counts[count].word == NULL) {
                for (int i = 0; i < count; i++) {
                    free(counts[i].word);
                }
                free(counts);
                return 0;
            }
            counts[count].count = 1;
            count++;
        }
    }

    qsort(counts, count, sizeof(WordCount), compare);

    *result = counts;
    return (count > n) ? n : count;
}

int main() {
    char text[] = "The quick brown fox jumps over the lazy dog. The dog is not amused. The quick brown fox is very quick.";
    int n = 3;
    WordCount *result;
    int numResults = findMostCommonWords(text, n, &result);

    for (int i = 0; i < numResults; i++) {
        printf("%s: %d\n", result[i].word, result[i].count);
        free(result[i].word);
    }
    free(result);

    return 0;
}