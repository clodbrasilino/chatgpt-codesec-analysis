#include <stdio.h>

int findExtraElementIndex(const int arr1[], const int arr2[], int n) {
    int left = 0;
    int right = n - 1;
    int index = n;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr1[mid] == arr2[mid]) {
            left = mid + 1;
        } else {
            index = mid;
            right = mid - 1;
        }
    }

    return index;
}

int main(void) {
    const int arr1[] = {1, 2, 3, 4, 5, 6, 7};
    const int arr2[] = {1, 2, 3, 5, 6, 7};
    
    size_t n_arr2 = sizeof(arr2) / sizeof(arr2[0]);

    int index = findExtraElementIndex(arr1, arr2, (int)n_arr2);
    
    printf("Index of the extra element is: %d\n", index);

    return 0;
}