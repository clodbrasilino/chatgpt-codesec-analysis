#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

int is_product_even(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (array[i] == 0) {
            return 1;
        }
        if (array[i] % 2 == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    int arr1[] = {1, 3, 5};
    int arr2[] = {1, 2, 5};
    int arr3[] = {0, 1, 3};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as pointer to const [constVariablePointer]
     */
    int *arr4 = NULL;

    printf("%s\n", is_product_even(arr1, sizeof(arr1) / sizeof(arr1[0])) ? "True" : "False");
    printf("%s\n", is_product_even(arr2, sizeof(arr2) / sizeof(arr2[0])) ? "True" : "False");
    printf("%s\n", is_product_even(arr3, sizeof(arr3) / sizeof(arr3[0])) ? "True" : "False");
    /* Possible weaknesses found:
     *  Condition 'is_product_even(arr4,0)' is always false
     *  Condition 'is_product_even(arr4,0)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_product_even' returns 0
     */
    printf("%s\n", is_product_even(arr4, 0) ? "True" : "False");

    return 0;
}