#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1024
#define CHAR_SET_SIZE 256

typedef struct {
    char character;
    int count;
} CharCount;

int compare(const void *a, const void *b) {
    return ((CharCount *)b)->count - ((CharCount *)a)->count;
}

void findCommonChars(const char *text, int *n) {
    int count[CHAR_SET_SIZE] = {0};
    for (size_t i = 0; text[i]; ++i) {
        if (isalpha(text[i])) {
            count[tolower(text[i])]++;
        }
    }

    *n = 0;
    for (size_t i = 0; i < CHAR_SET_SIZE; i++) {
        if (count[i] > 0) {
            (*n)++;
        }
    }

    CharCount *charCounts = (CharCount *)malloc(*n * sizeof(CharCount));
    if (!charCounts) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0, j = 0; i < CHAR_SET_SIZE; i++) {
        if (count[i] > 0) {
            charCounts[j].character = (char)i;
            charCounts[j].count = count[i];
            j++;
        }
    }

    qsort(charCounts, *n, sizeof(CharCount), compare);

    for (size_t i = 0; i < *n; i++) {
        printf("Character: %c, Count: %d\n", charCounts[i].character, charCounts[i].count);
    }

    free(charCounts);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[MAX_SIZE];
    int n;

    if (fgets(text, MAX_SIZE, stdin)) {
        size_t len = strcspn(text, "\n");
        if (len == MAX_SIZE - 1 && text[len - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (getchar() != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                if (getchar() == '\n') break;
            }
        } else {
            text[len] = '\0';
        }
    }
    findCommonChars(text, &n);
    return 0;
}