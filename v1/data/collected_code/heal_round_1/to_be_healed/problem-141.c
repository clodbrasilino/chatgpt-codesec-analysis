#include <stdio.h>

void flip(int arr[], int i) {
    int temp, start = 0;
    while (start < i) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[start]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        temp = arr[start];
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

int findMax(int arr[], int n) {
    int i, maxIndex = 0;
    for (i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'arr[maxIndex]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void pancakeSort(int arr[], int n) {
    for (int currSize = n; currSize > 1; currSize--) {
        int maxIndex = findMax(arr, currSize);
        if (maxIndex != currSize - 1) {
            flip(arr, maxIndex);
            flip(arr, currSize - 1);
        }
    }
}

int main() {
    int arr[] = {9, 5, 2, 8, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    pancakeSort(arr, n);
    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}