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

int longest_consecutive(const int *arr, int n) {
    if (n <= 0) {
        return 0;
    }
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }
    quick_sort(temp, 0, n - 1);
    int max_len = 1;
    int current_len = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) {
            continue;
        }
        if (temp[i] == temp[i - 1] + 1) {
            current_len++;
        } else {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 1;
        }
    }
    if (current_len > max_len) {
        max_len = current_len;
    }
    free(temp);
    return max_len;
}

int main() {
    int arr[] = {1, 9, 3, 10, 4, 20, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = longest_consecutive(arr, n);
    printf("%d\n", result);
    return 0;
}