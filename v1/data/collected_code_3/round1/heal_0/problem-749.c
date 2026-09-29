#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return atoi(*(char **)a) - atoi(*(char **)b);
}

void sortNumericalStrings(char *arr[], int n) {
    qsort(arr, n, sizeof(const char *), compare);
}

int main() {
    char *arr[] = {"10", "2", "30", "22", "100"};
    int n = sizeof(arr) / sizeof(char *);

    sortNumericalStrings(arr, n);

    for(int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }

    return 0;
}