#include <stdio.h>
#include <stdbool.h>

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
    
    printf("Product of {1, 3, 5, 7} is even: %s\n", 
           is_product_even(numbers1, 4) ? "true" : "false");
    
    printf("Product of {1, 3, 4, 7} is even: %s\n", 
           is_product_even(numbers2, 4) ? "true" : "false");
    
    printf("Product of {2, 4, 6} is even: %s\n", 
           is_product_even(numbers3, 3) ? "true" : "false");
    
    int empty[] = {0};
    printf("Product of empty array is even: %s\n", 
           is_product_even(empty, 0) ? "true" : "false");
    
    /* Possible weaknesses found:
     *  Assignment 'null_result=is_product_even(NULL,5)', assigned value is 0
     *  Calling function 'is_product_even' returns 0
     */
    bool null_result = is_product_even(NULL, 5);
    printf("Product of NULL array is even: %s\n", 
           /* Possible weaknesses found:
            *  Condition 'null_result' is always false
            *  Condition 'null_result' is always false [knownConditionTrueFalse]
            */
           null_result ? "true" : "false");
    
    return 0;
}