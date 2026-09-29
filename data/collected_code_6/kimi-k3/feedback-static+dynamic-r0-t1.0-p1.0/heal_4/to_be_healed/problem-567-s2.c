#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_sorted(const int arr[], size_t size) {
    if (size == 0) {
        return true;
    }
    
    if (arr == NULL) {
        return false;
    }
    
    if (size == 1) {
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
    int empty_list[] = {0};
    
    size_t sorted_size = sizeof(sorted_list) / sizeof(sorted_list[0]);
    size_t unsorted_size = sizeof(unsorted_list) / sizeof(unsorted_list[0]);
    size_t single_size = sizeof(single_element) / sizeof(single_element[0]);
    size_t empty_size = 0;
    
    bool result;
    
    result = is_sorted(sorted_list, sorted_size);
    printf("Sorted list: %s\n", result ? "true" : "false");
    
    result = is_sorted(unsorted_list, unsorted_size);
    printf("Unsorted list: %s\n", result ? "true" : "false");
    
    result = is_sorted(single_element, single_size);
    printf("Single element: %s\n", result ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Assignment 'result=is_sorted(empty_list,empty_size)', assigned value is 1
     *  Calling function 'is_sorted' returns 1
     */
    result = is_sorted(empty_list, empty_size);
    /* Possible weaknesses found:
     *  Condition 'result' is always true [knownConditionTrueFalse]
     *  Condition 'result' is always true
     */
    printf("Empty list: %s\n", result ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Condition 'is_sorted(NULL,5)' is always false
     *  Condition 'is_sorted(NULL,5)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_sorted' returns 0
     */
    if (is_sorted(NULL, 5)) {
        printf("NULL pointer: true\n");
    } else {
        printf("NULL pointer: false\n");
    }
    
    return 0;
}