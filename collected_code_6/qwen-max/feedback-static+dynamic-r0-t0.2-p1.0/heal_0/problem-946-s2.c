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

void findMostCommonElements(const char *text, CharCount *result, int *resultSize) {
    int counts[256] = {0};
    for (int i = 0; text[i] != '\0'; ++i) {
        counts[(unsigned char)text[i]]++;
    }

    *resultSize = 0;
    for (int i = 0; i < 256; ++i) {
        if (counts[i] > 0) {
            result[*resultSize].character = (char)i;
            result[*resultSize].count = counts[i];
            (*resultSize)++;
        }
    }

    qsort(result, *resultSize, sizeof(CharCount), compare);
}

int main() {
    const char *text = "hello world hello";
    CharCount result[256];
    int resultSize;

    findMostCommonElements(text, result, &resultSize);

    for (int i = 0; i < resultSize; ++i) {
        printf("Character: '%c', Count: %d\n", result[i].character, result[i].count);
    }

    return 0;
}