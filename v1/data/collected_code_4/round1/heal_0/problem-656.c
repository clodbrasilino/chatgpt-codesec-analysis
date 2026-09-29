#include <stdio.h>
#include <stdlib.h>

int minAbsoluteSumDifference(int* arr1, int size1, int* arr2, int size2) {
    if (size1 != size2 || arr1 == NULL || arr2 == NULL) {
        return -1;
    }
    
    int minSum = 0;
    for (int i = 0; i < size1; i++) {
        minSum += abs(arr1[i] - arr2[i]);
    }
    return minSum;
}

int main() {
    int arr1[] = {2, 3, 4, 5, 6};
    int arr2[] = {1, 7, 2, 9, 0};

    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    int result = minAbsoluteSumDifference(arr1, size1, arr2, size2);
    if (result != -1) {
        printf("The minimum sum of absolute differences of two arrays is %d\n", result);
    } else {
        printf("Error: Invalid arrays or sizes do not match\n");
    }

    return 0;
}