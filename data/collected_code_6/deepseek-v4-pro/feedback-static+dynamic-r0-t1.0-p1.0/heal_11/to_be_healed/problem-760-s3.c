#include <stdio.h>

int contains_single_distinct_element(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    int first = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] != first) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int arr1[] = {5, 5, 5, 5};
    int arr2[] = {5, 5, 7, 5};
    int arr3[] = {42};
    int arr4[] = {1, 2, 3, 4};

    int result1 = contains_single_distinct_element(arr1, sizeof(arr1) / sizeof(arr1[0]));
    int result2 = contains_single_distinct_element(arr2, sizeof(arr2) / sizeof(arr2[0]));
    int result3 = contains_single_distinct_element(arr3, sizeof(arr3) / sizeof(arr3[0]));
    int result4 = contains_single_distinct_element(arr4, sizeof(arr4) / sizeof(arr4[0]));

    printf("arr1: %s\n", result1 == 1 ? "yes" : "no");
    printf("arr2: %s\n", result2 == 1 ? "yes" : "no");
    printf("arr3: %s\n", result3 == 1 ? "yes" : "no");
    printf("arr4: %s\n", result4 == 1 ? "yes" : "no");

    /* Possible weaknesses found:
     *  Assignment 'null_result=contains_single_distinct_element(NULL,5)', assigned value is -1
     *  Calling function 'contains_single_distinct_element' returns -1
     */
    int null_result = contains_single_distinct_element(NULL, 5);
    /* Possible weaknesses found:
     *  Condition 'null_result==-1' is always true
     *  Condition 'null_result==-1' is always true [knownConditionTrueFalse]
     */
    if (null_result == -1) {
        printf("NULL: invalid input\n");
    } else {
        printf("NULL: %s\n", null_result == 1 ? "yes" : "no");
    }

    int zero_result = contains_single_distinct_element(arr1, 0);
    if (zero_result == -1) {
        printf("size 0: invalid input\n");
    } else {
        printf("size 0: %s\n", zero_result == 1 ? "yes" : "no");
    }

    return 0;
}