#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int count;
} StringCount;

int compare(const void *a, const void *b) {
    const StringCount *sa = (const StringCount *)a;
    const StringCount *sb = (const StringCount *)b;
    if (sa->count == sb->count) {
        return strcmp(sa->str, sb->str);
    }
    return sb->count - sa->count;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'bbb', got <no output>
  *  test case 1 failed: expected 'abc', got <no output>
  *  test case 2 failed: expected 'gsm', got <no output>
  */

char* secondMostFrequent(char *strings[], int size) {
    if (size < 2) {
        return NULL;
    }

    StringCount *counts = (StringCount *)calloc(size, sizeof(StringCount));
    if (counts == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(strings[i], counts[j].str) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            counts[i].str = strings[i];
            counts[i].count = 1;
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
    char *strings[] = {"bbb", "aaa", "ccc", "bbb", "aaa", "ccc"};
    int size = 6;

    char *secondMostFreq = secondMostFrequent(strings, size);
    if (secondMostFreq) {
        printf("Second most frequent: %s\n", secondMostFreq);
    } else {
        printf("No second most frequent string found.\n");
    }

    return 0;
}