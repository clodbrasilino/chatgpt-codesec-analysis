#include <stdio.h>
#include <stdlib.h>

int countInversionsType1(int arr[], int n) {
    int invCount = 0;
    if (arr == NULL || n <= 0) {
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                invCount++;
            }
        }
    }
    return invCount;
}

int countInversionsType2(int arr[], int n) {
    int invCount = 0;
    if (arr == NULL || n <= 0) {
        return 0;
    }
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            invCount++;
        }
    }
    return invCount;
}

int areInversionCountsSame(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }
    int count1 = countInversionsType1(arr, n);
    int count2 = countInversionsType2(arr, n);
    return count1 == count2;
}

int main(void) {
    int arr[] = {1, 3, 2, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (areInversionCountsSame(arr, n)) {
        printf("The counts of both types of inversions are the same.\n");
    } else {
        printf("The counts of both types of inversions are not the same.\n");
    }

    return 0;
}