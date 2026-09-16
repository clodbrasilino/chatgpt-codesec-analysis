#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

bool contains_consecutive_numbers(const int *arr, int size) {
    if (size <= 1) {
        return true;
    }
    if (arr == NULL) {
        return false;
    }
    
    int *temp = (int*)malloc(size * sizeof(int));
    if (temp == NULL) {
        return false;
    }
    
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    
    qsort(temp, size, sizeof(int), compare_ints);
    
    for (int i = 1; i < size; i++) {
        if (temp[i] - temp[i-1] != 1) {
            free(temp);
            return false;
        }
    }
    
    free(temp);
    return true;
}

int main(void) {
    const int arr1[] = {5, 2, 3, 1, 4};
    const int arr2[] = {34, 23, 52, 12, 3};
    const int arr3[] = {7, 6, 5, 5, 3, 4};
    const int arr4[] = {5};
    const int arr5[] = {1, 2, 3, 4, 5, 6, 7};
    const int arr6[] = {10, 11, 12, 14, 15};
    
    printf("Array 1: %s\n", contains_consecutive_numbers(arr1, 5) ? "true" : "false");
    printf("Array 2: %s\n", contains_consecutive_numbers(arr2, 5) ? "true" : "false");
    printf("Array 3: %s\n", contains_consecutive_numbers(arr3, 6) ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'contains_consecutive_numbers(arr4,1)' is always true
     *  Condition 'contains_consecutive_numbers(arr4,1)' is always true [knownConditionTrueFalse]
     *  Calling function 'contains_consecutive_numbers' returns 1
     */
    printf("Array 4: %s\n", contains_consecutive_numbers(arr4, 1) ? "true" : "false");
    printf("Array 5: %s\n", contains_consecutive_numbers(arr5, 7) ? "true" : "false");
    printf("Array 6: %s\n", contains_consecutive_numbers(arr6, 5) ? "true" : "false");
    /* Possible weaknesses found:
     *  Calling function 'contains_consecutive_numbers' returns 1
     *  Condition 'contains_consecutive_numbers(NULL,0)' is always true
     *  Condition 'contains_consecutive_numbers(NULL,0)' is always true [knownConditionTrueFalse]
     */
    printf("Empty array: %s\n", contains_consecutive_numbers(NULL, 0) ? "true" : "false");
    
    return 0;
}