#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got 1
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
    
    bool result1 = is_product_even(numbers1, 4);
    printf("Product of {1, 3, 5, 7} is even: %s\n", result1 ? "true" : "false");
    
    bool result2 = is_product_even(numbers2, 4);
    printf("Product of {1, 3, 4, 7} is even: %s\n", result2 ? "true" : "false");
    
    bool result3 = is_product_even(numbers3, 3);
    printf("Product of {2, 4, 6} is even: %s\n", result3 ? "true" : "false");
    
    printf("Product of NULL array is even: false\n");
    
    return 0;
}