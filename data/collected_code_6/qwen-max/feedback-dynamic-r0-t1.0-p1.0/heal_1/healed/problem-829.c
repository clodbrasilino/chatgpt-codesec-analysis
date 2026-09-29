#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *str;
    int count;
} StringCount;

int compare(const void *a, const void *b) {
    return ((StringCount *)b)->count - ((StringCount *)a)->count;
}

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

    int firstCount = INT_MAX, secondCount = INT_MIN;
    char *firstStr = "";
    for (int i = 0; i < n; ++i) {
        if (counts[i].count > secondCount && counts[i].count != firstCount) {
            secondCount = counts[i].count;
            if (secondCount > firstCount) {
                char *tempStr = firstStr;
                firstStr = counts[i].str;
                tempStr = counts[i].str;
            }
        }
    }

    free(counts);
    return (secondCount > 0) ? strdup(firstStr) : NULL;
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