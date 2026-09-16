#include <stdio.h>
#include <stdlib.h>

static int merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc((size_t)n1 * sizeof(int));
    int *R = (int *)malloc((size_t)n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        free(L);
        free(R);
        return -1;
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
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
    return 0;
}

static int merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        if (merge_sort(arr, left, mid) != 0) {
            return -1;
        }
        if (merge_sort(arr, mid + 1, right) != 0) {
            return -1;
        }
        if (merge(arr, left, mid, right) != 0) {
            return -1;
        }
    }
    return 0;
}

static void print_array(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = (int)(sizeof(arr) / sizeof(arr[0]));

    if (merge_sort(arr, 0, arr_size - 1) != 0) {
        fprintf(stderr, "Memory allocation failed during merge sort\n");
        return EXIT_FAILURE;
    }

    print_array(arr, arr_size);

    return EXIT_SUCCESS;
}