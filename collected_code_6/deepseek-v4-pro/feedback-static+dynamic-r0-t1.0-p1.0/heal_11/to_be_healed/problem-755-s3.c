#include <stdio.h>
#include <limits.h>

int second_smallest(const int arr[], int size, int *result) {
    if (arr == NULL || result == NULL || size < 2) {
        return -1;
    }

    int smallest = INT_MAX;
    int second = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (arr[i] < smallest) {
            second = smallest;
            smallest = arr[i];
        } else if (arr[i] < second && arr[i] != smallest) {
            second = arr[i];
        }
    }

    if (second == INT_MAX) {
        return -1;
    }

    *result = second;
    return 0;
}

int main(void) {
    int arr1[] = {5, 2, 8, 1, 9, 3};
    int arr2[] = {1, 1, 1, 1};
    int arr3[] = {10};
    int result;
    int ret;

    ret = second_smallest(arr1, sizeof(arr1) / sizeof(arr1[0]), &result);
    if (ret == 0) {
        printf("Second smallest: %d\n", result);
    } else {
        printf("No second smallest element found\n");
    }

    ret = second_smallest(arr2, sizeof(arr2) / sizeof(arr2[0]), &result);
    if (ret == 0) {
        printf("Second smallest: %d\n", result);
    } else {
        printf("No second smallest element found\n");
    }

    ret = second_smallest(arr3, sizeof(arr3) / sizeof(arr3[0]), &result);
    if (ret == 0) {
        printf("Second smallest: %d\n", result);
    } else {
        printf("No second smallest element found\n");
    }

    /* Possible weaknesses found:
     *  Calling function 'second_smallest' returns -1
     *  Assignment 'ret=second_smallest(NULL,5,&result)', assigned value is -1
     */
    ret = second_smallest(NULL, 5, &result);
    /* Possible weaknesses found:
     *  Condition 'ret==0' is always false
     *  Condition 'ret==0' is always false [knownConditionTrueFalse]
     */
    if (ret == 0) {
        printf("Second smallest: %d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}