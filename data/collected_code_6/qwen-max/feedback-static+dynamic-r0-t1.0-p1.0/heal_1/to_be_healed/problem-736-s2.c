#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int binary_search_left(int arr[], int n, int value) {
    int low = 0, high = n;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

int main() {
    int arr[] = {1, 4, 9, 16, 31, 56, 84};
    int n = sizeof(arr) / sizeof(arr[0]);
    int value = 31;
    int index = binary_search_left(arr, n, value);
    printf("The left insertion point for %d is: %d\n", value, index);
    return 0;
}