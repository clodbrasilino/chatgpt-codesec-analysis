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

void findCommonChars(const char *text, size_t text_len, int *n) {
    int count[CHAR_SET_SIZE] = {0};
    int i, j;

    for (i = 0; i < text_len; ++i) {
        if (isalpha(text[i])) {
            count[tolower(text[i])]++;
        }
    }

    CharCount *charCounts = (CharCount *)malloc(CHAR_SET_SIZE * sizeof(CharCount));
    if (!charCounts) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0, j = 0; i < CHAR_SET_SIZE; i++) {
        if (count[i] > 0) {
            charCounts[j].character = (char)i;
            charCounts[j].count = count[i];
            j++;
        }
    }
    *n = j;

    qsort(charCounts, *n, sizeof(CharCount), compare);

    for (i = 0; i < *n; i++) {
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
        text[len] = '\0';
        findCommonChars(text, len, &n);
    } else {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }
    return 0;
}