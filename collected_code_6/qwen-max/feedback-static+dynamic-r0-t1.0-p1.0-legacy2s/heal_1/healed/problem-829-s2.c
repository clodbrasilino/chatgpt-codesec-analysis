#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int count;
} StringCount;

int compare(const void *a, const void *b) {
    StringCount *sa = (StringCount *)a;
    StringCount *sb = (StringCount *)b;
    if (sa->count == sb->count) {
        return strcmp(sa->str, sb->str);
    }
    return sb->count - sa->count;
}

char* secondMostFrequent(char *strings[], int size) {
    if (size < 2) {
        return NULL;
    }

    StringCount *counts = (StringCount *)malloc(size * sizeof(StringCount));
    memset(counts, 0, size * sizeof(StringCount));

    for (int i = 0; i < size; i++) {
        counts[i].str = strings[i];
        counts[i].count = 1;
        for (int j = i + 1; j < size; j++) {
            if (strcmp(strings[i], strings[j]) == 0) {
                counts[j].str = NULL;
                counts[i].count++;
            }
        }
    }

    qsort(counts, size, sizeof(StringCount), compare);

    for (int i = 1; i < size; i++) {
        if (counts[i].str && counts[i].count < counts[0].count) {
            char *result = counts[i].str;
            free(counts);
            return result;
        }
    }

    free(counts);
    return NULL;
}

int main() {
    char *strings[] = {"apple", "banana", "apple", "orange", "banana", "banana"};
    int size = 6;

    char *secondMostFreq = secondMostFrequent(strings, size);
    if (secondMostFreq) {
        printf("Second most frequent: %s\n", secondMostFreq);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}