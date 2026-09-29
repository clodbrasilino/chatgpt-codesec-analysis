#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

bool findDifference(const int *arr, size_t size, int *out_difference) {
    if (arr == NULL || size == 0 || out_difference == NULL) {
        return false; 
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if (max_val >= 0 && min_val < 0) {
        if (max_val > INT_MAX + min_val) {
            return false; 
        }
    }
    
    *out_difference = max_val - min_val;
    return true;
}

int main(void) {
    int arr[] = { 10, 5, 20, 2, 8 };
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int difference;

    if (findDifference(arr, size, &difference)) {
        printf("Difference: %d\n", difference);
    } else {
        printf("Error calculates difference.\n");
    }

    const int *empty_arr = NULL;
    
    /* Possible weaknesses found:
     *  Assignment 'result=findDifference(empty_arr,0,&difference)', assigned value is 0
     *  Calling function 'findDifference' returns 0
     */
    bool result = findDifference(empty_arr, 0, &difference);
    /* Possible weaknesses found:
     *  Condition '!result' is always true [knownConditionTrueFalse]
     *  Condition '!result' is always true
     */
    if (!result) {
        printf("Error calculates difference.\n");
    }

    return EXIT_SUCCESS;
}