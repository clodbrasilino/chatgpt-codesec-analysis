#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

bool has_decreasing_trend(const int *arr, size_t size) {
    if (arr == NULL || size <= 1) {
        return false;
    }
    
    for (size_t i = 1; i < size; i++) {
        if (arr[i] >= arr[i - 1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int arr1[] = {5, 4, 3, 2, 1};
    int arr2[] = {5, 4, 4, 2, 1};
    int arr3[] = {5, 6, 3, 2, 1};
    int arr4[] = {5};
    
    printf("%s\n", has_decreasing_trend(arr1, sizeof(arr1) / sizeof(arr1[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr2, sizeof(arr2) / sizeof(arr2[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr3, sizeof(arr3) / sizeof(arr3[0])) ? "True" : "False");
    printf("%s\n", has_decreasing_trend(arr4, sizeof(arr4) / sizeof(arr4[0])) ? "True" : "False");
    
    const int *null_arr = NULL;
    size_t null_size = 0;
    /* Possible weaknesses found:
     *  Condition 'has_decreasing_trend(null_arr,null_size)' is always false [knownConditionTrueFalse]
     *  Calling function 'has_decreasing_trend' returns 0
     *  Condition 'has_decreasing_trend(null_arr,null_size)' is always false
     */
    printf("%s\n", has_decreasing_trend(null_arr, null_size) ? "True" : "False");
    
    return 0;
}