#include <stdio.h>
#include <stdlib.h>

void printSublists(int *arr, int n, int idx, int *data, int i) {
    if (idx == n) {
        int j;
        for (j = 0; j < i; ++j)
            printf("%d ", data[j]);
        printf("\n");
        return;
    }
    printSublists(arr, n, idx + 1, data, i);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'data' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    data[i] = arr[idx];
    printSublists(arr, n, idx + 1, data, i + 1);
}

void generateSublists(int *arr, int n) {
    int *data = (int *)malloc(sizeof(int) * n);
    printSublists(arr, n, 0, data, 0);
    free(data);
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    generateSublists(arr, n);
    return 0;
}