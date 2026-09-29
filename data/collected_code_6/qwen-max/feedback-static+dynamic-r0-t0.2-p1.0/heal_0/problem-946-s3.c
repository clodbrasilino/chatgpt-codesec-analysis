#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CHAR 256

typedef struct {
    char character;
    int count;
} CharCount;

int compare(const void *a, const void *b) {
    return ((CharCount *)b)->count - ((CharCount *)a)->count;
}

void findMostCommonElements(const char *text, int *mostCommon, int *count) {
    CharCount charCounts[MAX_CHAR] = {0};
    int maxCount = 0;

    for (int i = 0; text[i] != '\0'; ++i) {
        charCounts[(unsigned char)text[i]].character = text[i];
        charCounts[(unsigned char)text[i]].count++;
        if (charCounts[(unsigned char)text[i]].count > maxCount) {
            maxCount = charCounts[(unsigned char)text[i]].count;
        }
    }

    qsort(charCounts, MAX_CHAR, sizeof(CharCount), compare);

    for (int i = 0; i < MAX_CHAR && charCounts[i].count == maxCount; ++i) {
        mostCommon[i] = charCounts[i].character;
        count[i] = charCounts[i].count;
    }
}

int main() {
    const char *text = "example text with some characters";
    int mostCommon[MAX_CHAR] = {0};
    int count[MAX_CHAR] = {0};

    findMostCommonElements(text, mostCommon, count);

    for (int i = 0; i < MAX_CHAR && mostCommon[i] != 0; ++i) {
        printf("Character: %c, Count: %d\n", mostCommon[i], count[i]);
    }

    return 0;
}