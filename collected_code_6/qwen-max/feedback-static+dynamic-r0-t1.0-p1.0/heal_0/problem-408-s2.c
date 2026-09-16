#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void findPairs(int *arr1, int *arr2, int n, int m, int k, Pair *result) {
    qsort(arr1, n, sizeof(int), cmp);
    qsort(arr2, m, sizeof(int), cmp);

    for (int i = 0, j = m - 1; i < n && j >= 0 && k > 0; k--) {
        result[k-1].first = arr1[i];
        result[k-1].second = arr2[j];
        i++;
        j--;
    }
}

int main() {
    int arr1[] = {3, 1, 4};
    int arr2[] = {2, 5, 6};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);
    int k = 3;

    Pair *result = (Pair *)malloc(k * sizeof(Pair));
    if (result == NULL) {
        return 1;
    }

    findPairs(arr1, arr2, n, m, k, result);

    for (int i = 0; i < k; i++) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    free(result);
    return 0;
}