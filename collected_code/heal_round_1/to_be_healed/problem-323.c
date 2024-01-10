#include <stdio.h>

void rearrangeArray(int arr[], int n) {
    int positiveIndex = 0;
    int negativeIndex = 1;

    while (positiveIndex < n && negativeIndex < n) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[positiveIndex]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (positiveIndex < n && arr[positiveIndex] >= 0) {
            positiveIndex += 2;
        }

        /* Possible weaknesses found:
         *  Cannot determine that 'arr[negative_Index]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        while (negativeIndex < n && arr[negativeIndex] <= 0) {
            negativeIndex += 2;
        }

        if (positiveIndex < n && negativeIndex < n) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[positiveIndex]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            int temp = arr[positiveIndex];
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[negative_Index]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            arr[positiveIndex] = arr[negativeIndex];
            arr[negativeIndex] = temp;
        }
    }
}

int main() {
    int arr[] = {-1, 2, -3, 4, 5, 6, -7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    rearrangeArray(arr, n);

    printf("\nRearranged array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}