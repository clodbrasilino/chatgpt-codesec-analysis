#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char character;
    int count;
} CharCount;

int compare(const void *a, const void *b) {
    return ((CharCount *)b)->count - ((CharCount *)a)->count;
}

void findMostCommonElements(const char *text, int *mostCommon, int *counts, int *numUnique) {
    int freq[256] = {0};
    for (int i = 0; text[i] != '\0'; ++i) {
        if (text[i] != ' ') {
            freq[(unsigned char)text[i]]++;
        }
    }

    *numUnique = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            (*numUnique)++;
        }
    }

    CharCount *charCounts = (CharCount *)malloc(*numUnique * sizeof(CharCount));
    if (charCounts == NULL) {
        *numUnique = 0;
        return;
    }

    int index = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            charCounts[index].character = (char)i;
            charCounts[index].count = freq[i];
            index++;
        }
    }

    qsort(charCounts, *numUnique, sizeof(CharCount), compare);

    for (int i = 0; i < *numUnique && i < 10; ++i) {
        mostCommon[i] = charCounts[i].character;
        counts[i] = charCounts[i].count;
    }

    free(charCounts);
}

int main() {
    const char *text = "hello world hello";
    int mostCommon[10];
    int counts[10];
    int numUnique;

    findMostCommonElements(text, mostCommon, counts, &numUnique);

    for (int i = 0; i < numUnique && i < 10; ++i) {
        printf("Character: %c, Count: %d\n", mostCommon[i], counts[i]);
    }

    return 0;
}