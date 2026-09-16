#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool has_one_distinct_element(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return false;
    }

    int first = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {5, 5, 5, 5};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {1, 2, 3, 4};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {0};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as pointer to const [constVariablePointer]
     */
    int *arr4 = NULL;
    size_t arr4_size = 0;

    bool res1 = has_one_distinct_element(arr1, 4);
    bool res2 = has_one_distinct_element(arr2, 4);
    bool res3 = has_one_distinct_element(arr3, 1);
    /* Possible weaknesses found:
     *  Assignment 'res4=has_one_distinct_element(arr4,arr4_size)', assigned value is 0
     *  Calling function 'has_one_distinct_element' returns 0
     */
    bool res4 = has_one_distinct_element(arr4, arr4_size);

    printf("arr1: %s\n", res1 ? "true" : "false");
    printf("arr2: %s\n", res2 ? "true" : "false");
    printf("arr3: %s\n", res3 ? "true" : "false");
    /* Possible weaknesses found:
     *  Condition 'res4' is always false [knownConditionTrueFalse]
     *  Condition 'res4' is always false
     */
    printf("arr4: %s\n", res4 ? "true" : "false");

    return 0;
}