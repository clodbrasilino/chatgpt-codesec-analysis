#include <stdio.h>
#include <stdlib.h>

int isSubset(int arr1[], int size1, int arr2[], int size2) {
    if (size2 == 0) return 1;
    if (size1 == 0) return 0;

    for (int i = 0; i < size2; i++) {
        int found = 0;
        for (int j = 0; j < size1; j++) {
            if (arr2[i] == arr1[j]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main(void) {
    int arr1[] = {11, 1, 13, 21, 3, 7};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);

    int arr2[] = {11, 3, 7, 1};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    int result = isSubset(arr1, size1, arr2, size2);
    if (result) {
        printf("arr2[] is subset of arr1[]\n");
    } else {
        printf("arr2[] is not a subset of arr1[]\n");
    }

    return 0;
}