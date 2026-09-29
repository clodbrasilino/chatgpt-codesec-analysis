#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int min_elements_to_remove(int arr[], int n, int k) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    qsort(arr, n, sizeof(int), compare);

    int max_length = 0;
    int left = 0;

    for (int right = 0; right < n; right++) {
        while (arr[right] - arr[left] > k) {
            left++;
        }
        int current_length = right - left + 1;
        if (current_length > max_length) {
            max_length = current_length;
        }
    }

    return n - max_length;
}

int main(void) {
    int arr[] = {1, 3, 4, 9, 10, 11, 12, 17, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;

    int result = min_elements_to_remove(arr, n, k);
    printf("%d\n", result);

    return 0;
}