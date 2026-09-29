#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canBeSortedByCornerElements(const int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    if (n <= 2) {
        return true;
    }

    int *deque = (int *)malloc(n * sizeof(int));
    if (deque == NULL) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        deque[i] = arr[i];
    }

    int left = 0;
    int right = n - 1;
    bool result = true;

    for (int i = 0; i < n; i++) {
        int val = arr[i];
        
        if (left > right) {
            break;
        }

        int left_val = deque[left];
        int right_val = deque[right];

        if (val < left_val && val < right_val) {
            result = false;
            break;
        }
        
        if (val > left_val && val > right_val) {
            result = false;
            break;
        }

        if (left_val <= right_val) {
            left++;
        } else {
            right--;
        }
    }

    free(deque);
    return result;
}

int main(void) {
    int arr1[] = {1, 3, 2, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", canBeSortedByCornerElements(arr1, n1));

    int arr2[] = {3, 1, 4, 2};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", canBeSortedByCornerElements(arr2, n2));

    int arr3[] = {1, 2, 3, 4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", canBeSortedByCornerElements(arr3, n3));

    return 0;
}