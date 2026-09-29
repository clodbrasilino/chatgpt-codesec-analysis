#include <stdio.h>
#include <stdlib.h>

void removeNegatives(int *arr, int *n) {
    int *temp = (int*)malloc(*n * sizeof(int));
    int j = 0;
    for (int i = 0; i < *n; i++) {
        if (arr[i] >= 0) {
            temp[j++] = arr[i];
        }
    }
    *n = j;
    free(arr);
    arr = (int*)realloc(temp, *n * sizeof(int));
    if (arr != NULL) {
        for (int i = 0; i < *n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(1);
    }
}

int main() {
    int n = 5;
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    arr[0] = -1;
    arr[1] = 2;
    arr[2] = -3;
    arr[3] = 4;
    arr[4] = 5;

    removeNegatives(arr, &n);

    free(arr);
    return 0;
}