#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int* find_triplet(int *arr, int n, int target) {
    if (arr == NULL || n < 3) {
        return NULL;
    }
    int *result = (int*)malloc(3 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    quick_sort(arr, 0, n - 1);
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) {
            continue;
        }
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            long long current_sum = (long long)arr[i] + arr[left] + arr[right];
            if (current_sum == target) {
                result[0] = arr[i];
                result[1] = arr[left];
                result[2] = arr[right];
                return result;
            } else if (current_sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    free(result);
    return NULL;
}

int main() {
    int arr[] = {12, 3, 4, 1, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 24;
    int *triplet = find_triplet(arr, n, target);
    if (triplet != NULL) {
        printf("%d %d %d\n", triplet[0], triplet[1], triplet[2]);
        free(triplet);
    } else {
        printf("No triplet found\n");
    }
    return 0;
}