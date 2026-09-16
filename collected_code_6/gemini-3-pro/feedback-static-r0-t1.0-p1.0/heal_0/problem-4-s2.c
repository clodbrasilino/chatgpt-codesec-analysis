#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void buildMinHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int* findLargestIntegers(int arr[], int n, int k) {
    if (n <= 0 || k <= 0 || arr == NULL) {
        return NULL;
    }

    if (k > n) {
        k = n;
    }

    int *result = (int *)malloc(k * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        result[i] = arr[i];
    }

    buildMinHeap(result, k);

    for (int i = k; i < n; i++) {
        if (arr[i] > result[0]) {
            result[0] = arr[i];
            heapify(result, k, 0);
        }
    }

    return result;
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    int *largestList = findLargestIntegers(arr, n, k);

    if (largestList != NULL) {
        for (int i = 0; i < k; i++) {
            printf("%d ", largestList[i]);
        }
        printf("\n");
        free(largestList);
    } else {
        printf("Error: Could not allocate memory or invalid input.\n");
    }

    return 0;
}