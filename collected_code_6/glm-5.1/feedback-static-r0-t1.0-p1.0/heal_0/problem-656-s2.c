#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        free(L);
        free(R);
        return;
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

long long findMinSum(int a[], int b[], int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return 0;
    }

    mergeSort(a, 0, n - 1);
    mergeSort(b, 0, n - 1);

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long diff = (long long)a[i] - b[i];
        if (diff < 0) {
            diff = -diff;
        }
        sum += diff;
    }

    return sum;
}

int main() {
    int a[] = {3, 2, 1};
    int b[] = {2, 1, 3};
    int n = sizeof(a) / sizeof(a[0]);

    long long result = findMinSum(a, b, n);
    printf("%lld\n", result);

    return 0;
}