#include <stdio.h>

void moveZeroesToEnd(int arr[], int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] != 0) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            arr[count++] = arr[i];
        }
    }

    while (count < n) {
        arr[count++] = 0;
    }
}

int main() {
    int arr[] = {1, 2, 0, 4, 0, 5, 0, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    moveZeroesToEnd(arr, n);

    printf("Array after moving zeroes to the end: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}