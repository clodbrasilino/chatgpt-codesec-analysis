#include <stdio.h>
#include <stdlib.h>

int sum_repeated_elements(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    int *count = (int *)calloc(size, sizeof(int));
    if (count == NULL) {
        return 0;
    }

    int sum = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int occurrence = 0;
            for (int j = i; j < size; j++) {
                if (arr[i] == arr[j]) {
                    occurrence++;
                }
            }
            if (occurrence > 1) {
                sum += arr[i];
            }
        }
    }

    free(count);
    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 1, 5, 2};
    int size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_repeated_elements(arr, size);
    printf("%d\n", result);

    return 0;
}