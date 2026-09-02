#include <stdbool.h>
#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
bool isMinHeap(int arr[], int n) {
    for (int i = 0; i < (n - 2) / 2; ++i) {
        if (arr[i] > arr[2 * i + 1] || (2 * i + 2 < n && arr[i] > arr[2 * i + 2])) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {1, 3, 6, 5, 9, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (isMinHeap(arr, n)) {
        printf("The array represents a min heap.\n");
    } else {
        printf("The array does not represent a min heap.\n");
    }
    return 0;
}