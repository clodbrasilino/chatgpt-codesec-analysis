#include <stdio.h>
#include <stdlib.h>

int is_product_even(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
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
    
    printf("%s\n", is_product_even(arr1, sizeof(arr1) / sizeof(arr1[0])) ? "True" : "False");
    printf("%s\n", is_product_even(arr2, sizeof(arr2) / sizeof(arr2[0])) ? "True" : "False");
    printf("%s\n", is_product_even(arr3, sizeof(arr3) / sizeof(arr3[0])) ? "True" : "False");
    /* Possible weaknesses found:
     *  Condition 'is_product_even(NULL,0)' is always false [knownConditionTrueFalse]
     *  Condition 'is_product_even(NULL,0)' is always false
     *  Calling function 'is_product_even' returns 0
     */
    printf("%s\n", is_product_even(NULL, 0) ? "True" : "False");

    return 0;
}