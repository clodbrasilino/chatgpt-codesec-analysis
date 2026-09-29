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

void findCommonChars(char *text, int *n) {
    int count[CHAR_SET_SIZE] = {0};
    int i, j;
    
    for (i = 0; text[i]; ++i) {
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
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(text);
        if (len > 0 && text[len - 1] == '\n') {
            text[len - 1] = '\0';
        }
    }
    findCommonChars(text, &n);
    return 0;
}