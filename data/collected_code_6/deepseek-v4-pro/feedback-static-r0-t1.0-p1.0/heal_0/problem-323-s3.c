#include <stdio.h>
#include <stdlib.h>

void rearrange(int arr[], int n) {
    int *pos = (int *)malloc(n * sizeof(int));
    int *neg = (int *)malloc(n * sizeof(int));
    int pos_count = 0, neg_count = 0;
    int i, j = 0, k = 0;

    if (pos == NULL || neg == NULL) {
        free(pos);
        free(neg);
        return;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] >= 0) {
            pos[pos_count++] = arr[i];
        } else {
            neg[neg_count++] = arr[i];
        }
    }

    i = 0;
    j = 0;
    k = 0;

    while (i < pos_count && j < neg_count) {
        arr[k++] = pos[i++];
        arr[k++] = neg[j++];
    }

    while (i < pos_count) {
        arr[k++] = pos[i++];
    }

    while (j < neg_count) {
        arr[k++] = neg[j++];
    }

    free(pos);
    free(neg);
}

int main(void) {
    int arr[] = {1, 2, 3, -4, -1, 4, -3, -2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    rearrange(arr, n);

    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}