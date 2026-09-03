#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char *str;
    int count;
} StringCount;

int compare(const void *a, const void *b) {
    return ((StringCount *)a)->count - ((StringCount *)b)->count;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'abc', got bcd
  *  test case 2 failed: expected 'gsm', got cdma
  *  test case 0 failed: expected 'bbb', got aaa
  */

char *secondMostFrequent(char *arr[], int n) {
    if (n < 2) return NULL;

    StringCount *counts = (StringCount *)malloc(n * sizeof(StringCount));
    for (int i = 0; i < n; ++i) {
        counts[i].str = arr[i];
        counts[i].count = 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (strcmp(arr[i], arr[j]) == 0) {
                counts[i].count++;
                counts[j].count = 0;
            }
        }
    }

    qsort(counts, n, sizeof(StringCount), compare);

    for (int i = n - 1; i >= 0; --i) {
        if (counts[i].count > 0 && (i == n - 1 || counts[i].count < counts[i + 1].count)) {
            char *secondMostFreq = counts[i].str;
            free(counts);
            return strdup(secondMostFreq);
        }
    }

    free(counts);
    return NULL;
}

int main() {
    char *arr[] = {"apple", "banana", "apple", "orange", "banana", "banana", "grape", "grape"};
    int n = sizeof(arr) / sizeof(arr[0]);
    char *result = secondMostFrequent(arr, n);
    if (result) {
        printf("Second most frequent string: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found.\n");
    }
    return 0;
}