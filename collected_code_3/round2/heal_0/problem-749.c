#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return atoi(*(char **)a) - atoi(*(char **)b);
}

void sortStringsNumerically(char *arr[], int n) {
    qsort(arr, n, sizeof(const char *), compare);
}

int main() {
    char *arr[] = {"10", "20", "9", "100"};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    sortStringsNumerically(arr, n);

    for (i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }

    return 0;
}