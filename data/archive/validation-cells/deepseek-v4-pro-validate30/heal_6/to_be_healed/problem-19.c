#include <stdio.h>
#include <stdlib.h>

int contains_duplicate(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    if (size == 1) {
        return 0;
    }

    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    for (int i = 1; i < size; i++) {
        int key = temp[i];
        int j = i - 1;
        while (j >= 0 && temp[j] > key) {
            temp[j + 1] = temp[j];
            j--;
        }
        temp[j + 1] = key;
    }

    for (int i = 0; i < size - 1; i++) {
        if (temp[i] == temp[i + 1]) {
            free(temp);
            return 1;
        }
    }

    free(temp);
    return 0;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = contains_duplicate(arr1, size1);
    printf("Array 1 has duplicates: %s\n", result1 == 1 ? "Yes" : "No");

    int arr2[] = {1, 2, 3, 2, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = contains_duplicate(arr2, size2);
    printf("Array 2 has duplicates: %s\n", result2 == 1 ? "Yes" : "No");

    int arr3[] = {5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = contains_duplicate(arr3, size3);
    printf("Array 3 has duplicates: %s\n", result3 == 1 ? "Yes" : "No");

    /* Possible weaknesses found:
     *  Assignment 'result4=contains_duplicate(NULL,5)', assigned value is -1
     *  Calling function 'contains_duplicate' returns -1
     */
    int result4 = contains_duplicate(NULL, 5);
    /* Possible weaknesses found:
     *  Condition 'result4==-1' is always true [knownConditionTrueFalse]
     *  Condition 'result4==-1' is always true
     */
    if (result4 == -1) {
        printf("Error: Invalid input\n");
    } else {
        printf("Array 4 has duplicates: %s\n", result4 == 1 ? "Yes" : "No");
    }

    return 0;
}