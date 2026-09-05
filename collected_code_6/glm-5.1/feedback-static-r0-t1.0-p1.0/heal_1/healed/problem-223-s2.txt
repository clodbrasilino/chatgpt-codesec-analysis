#include <stdio.h>
#include <stddef.h>

int is_majority(const int arr[], size_t n, int x) {
    if (n == 0) {
        return 0;
    }
    
    size_t low = 0;
    size_t high = n - 1;
    size_t first_occurrence = n;
    
    while (low <= high) {
        size_t mid = low + (high - low) / 2;
        if (arr[mid] >= x) {
            if (arr[mid] == x) {
                first_occurrence = mid;
            }
            if (mid == 0) {
                break;
            }
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    if (first_occurrence == n || (first_occurrence + n / 2 >= n) || arr[first_occurrence + n / 2] != x) {
        return 0;
    }
    
    return 1;
}

int main(void) {
    int arr1[] = {1, 2, 2, 2, 2, 3, 4};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    int res1 = is_majority(arr1, n1, 2);
    printf("%d\n", res1);

    int arr2[] = {1, 1, 2, 2, 3, 3, 3};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    int res2 = is_majority(arr2, n2, 2);
    printf("%d\n", res2);
    
    int arr3[] = {2, 2, 2, 2, 2, 2, 2};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    int res3 = is_majority(arr3, n3, 2);
    printf("%d\n", res3);

    return 0;
}