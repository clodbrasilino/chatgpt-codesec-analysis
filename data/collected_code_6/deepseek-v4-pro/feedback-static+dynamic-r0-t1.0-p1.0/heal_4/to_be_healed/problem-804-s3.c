#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

bool is_product_even(const int numbers[], int length) {
    if (numbers == NULL || length <= 0) {
        return false;
    }
    
    for (int i = 0; i < length; i++) {
        if (numbers[i] % 2 == 0) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    int numbers1[] = {1, 3, 5, 7};
    int numbers2[] = {1, 3, 4, 7};
    int numbers3[] = {2, 4, 6};
    
    if (is_product_even(numbers1, 4)) {
        printf("Product of {1, 3, 5, 7} is even: true\n");
    } else {
        printf("Product of {1, 3, 5, 7} is even: false\n");
    }
    
    if (is_product_even(numbers2, 4)) {
        printf("Product of {1, 3, 4, 7} is even: true\n");
    } else {
        printf("Product of {1, 3, 4, 7} is even: false\n");
    }
    
    if (is_product_even(numbers3, 3)) {
        printf("Product of {2, 4, 6} is even: true\n");
    } else {
        printf("Product of {2, 4, 6} is even: false\n");
    }
    
    /* Possible weaknesses found:
     *  Condition 'is_product_even(NULL,5)' is always false
     *  Condition 'is_product_even(NULL,5)' is always false [knownConditionTrueFalse]
     *  Calling function 'is_product_even' returns 0
     */
    if (is_product_even(NULL, 5)) {
        printf("Product of NULL array is even: true\n");
    } else {
        printf("Product of NULL array is even: false\n");
    }
    
    return 0;
}