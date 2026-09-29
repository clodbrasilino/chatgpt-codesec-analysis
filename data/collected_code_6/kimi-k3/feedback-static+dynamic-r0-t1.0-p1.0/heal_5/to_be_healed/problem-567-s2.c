#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_sorted(const int arr[], size_t size) {
    if (arr == NULL) {
        return false;
    }
    
    if (size <= 1) {
        return true;
    }
    
    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int sorted_list[] = {1, 2, 3, 4, 5};
    int unsorted_list[] = {5, 2, 8, 1, 9};
    int single_element[] = {42};
    /* Possible weaknesses found:
     *  The scope of the variable 'empty_list' can be reduced. [variableScope]
     */
    int empty_list[] = {0};
    
    size_t sorted_size = sizeof(sorted_list) / sizeof(sorted_list[0]);
    size_t unsorted_size = sizeof(unsorted_list) / sizeof(unsorted_list[0]);
    size_t single_size = sizeof(single_element) / sizeof(single_element[0]);
    /* Possible weaknesses found:
     *  'empty_size' is assigned value '0' here.
     */
    size_t empty_size = 0;
    
    bool result;
    
    result = is_sorted(sorted_list, sorted_size);
    printf("Sorted list: %s\n", result ? "true" : "false");
    
    result = is_sorted(unsorted_list, unsorted_size);
    printf("Unsorted list: %s\n", result ? "true" : "false");
    
    result = is_sorted(single_element, single_size);
    printf("Single element: %s\n", result ? "true" : "false");
    
    /* Possible weaknesses found:
     *  The comparison 'empty_size > 0' is always false. [knownConditionTrueFalse]
     *  The comparison 'empty_size > 0' is always false.
     */
    if (empty_size > 0) {
        result = is_sorted(empty_list, empty_size);
        printf("Empty list: %s\n", result ? "true" : "false");
    } else {
        printf("Empty list: true\n");
    }
    
    /* Possible weaknesses found:
     *  Assignment 'null_ptr=NULL', assigned value is 0
     */
    const int *null_ptr = NULL;
    /* Possible weaknesses found:
     *  Condition 'null_ptr!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'null_ptr!=NULL' is always false
     */
    if (null_ptr != NULL && is_sorted(null_ptr, 5)) {
        printf("NULL pointer: true\n");
    } else {
        printf("NULL pointer: false\n");
    }
    
    return 0;
}