#include <stdio.h>
#include <stdbool.h>

bool isSubArray(int *arr1, int size1, int *arr2, int size2) {
    if (size2 > size1)
        return false;

    int i = 0;
    int j = 0;

    while (i < size1 && j < size2) {
        if (arr1[i] == arr2[j]) {
            i++;
            j++;
            if (j == size2) {
                return true;
            }
        } else {
            i++;
            j = 0;
        }
    }

    return false;
}

int main() {
    int arr1[] = {1,2,3,4,5,6,7,8,9};
    int arr2[] = {3,4,5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    if(isSubArray(arr1, size1, arr2, size2))
        printf("Array 2 is a subarray of Array 1\n");
    else
        printf("Array 2 is not a subarray of Array 1\n");

    return 0;
}    