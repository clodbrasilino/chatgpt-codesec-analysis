#include <stdio.h>

int contains_single_distinct_element(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
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
    const int *null_arr = NULL;
    /* Possible weaknesses found:
     *  Assignment 'null_result=contains_single_distinct_element(null_arr,5)', assigned value is 0
     *  Calling function 'contains_single_distinct_element' returns 0
     */
    int null_result = contains_single_distinct_element(null_arr, 5);
    int zero_result = contains_single_distinct_element(arr1, 0);
    
    printf("arr1: %s\n", contains_single_distinct_element(arr1, sizeof(arr1) / sizeof(arr1[0])) ? "yes" : "no");
    printf("arr2: %s\n", contains_single_distinct_element(arr2, sizeof(arr2) / sizeof(arr2[0])) ? "yes" : "no");
    printf("arr3: %s\n", contains_single_distinct_element(arr3, sizeof(arr3) / sizeof(arr3[0])) ? "yes" : "no");
    printf("arr4: %s\n", contains_single_distinct_element(arr4, sizeof(arr4) / sizeof(arr4[0])) ? "yes" : "no");
    /* Possible weaknesses found:
     *  Condition 'null_result' is always false
     *  Condition 'null_result' is always false [knownConditionTrueFalse]
     */
    printf("NULL: %s\n", null_result ? "yes" : "no");
    printf("size 0: %s\n", zero_result ? "yes" : "no");
    
    return 0;
}