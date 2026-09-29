#include <stdio.h>

void reverseArray(int arr[], int n, int pos) {
    int start = 0;
    int end = pos - 1;

    while (start < end) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[start]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        int temp = arr[start];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[end]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int pos = 3;

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    reverseArray(arr, n, pos);

    printf("\nReversed array upto position %d: ", pos);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}