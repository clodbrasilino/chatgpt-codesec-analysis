#include <stdio.h>

int isSubArray(int arr1[], int n1, int arr2[], int n2) {
    int i, j;

    // Traverse both arrays
    for (i = 0, j = 0; i < n1 && j < n2; i++) {

        // If current element of arr1 matches with first element of arr2,
        // move both pointers to next elements in their respective arrays
        if (arr1[i] == arr2[j]) {
            j++;
        } else {
            // If the current element of arr1 doesn't match with current element of arr2,
            // reset j and continue comparing with next element of arr2
            j = 0;
        }
    }

    // If all elements of arr2 are found in arr1, then it is a subarray
    if (j == n2) {
        return 1; // arr2 is a subarray of arr1
    } else {
        return 0; // arr2 is not a subarray of arr1
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {3, 4, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    if (isSubArray(arr1, n1, arr2, n2)) {
        printf("arr2 is a subarray of arr1");
    } else {
        printf("arr2 is not a subarray of arr1");
    }

    return 0;
}