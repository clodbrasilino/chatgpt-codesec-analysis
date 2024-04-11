#include <stdio.h>
#include <stdbool.h>

bool isSubArray(int *array1, int size1, int *array2, int size2) {
    int i, j;
    for (i = 0; i <= size1 - size2; i++) {
        for (j = 0; j < size2; j++) {
            if (array1[i + j] != array2[j]) {
                break;
            }
        }
        if (j == size2) {
            return true;
        }
    }
    return false;
}

int main() {
    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int array2[] = {5, 6, 7, 8};
    int size1 = sizeof(array1) / sizeof(array1[0]);
    int size2 = sizeof(array2) / sizeof(array2[0]);

    if (isSubArray(array1, size1, array2, size2)) {
        printf("Array2 is a subarray of Array1\n");
    } else {
        printf("Array2 is not a subarray of Array1\n");
    }

    return 0;
}