#include <stdio.h>

int is_product_even(const int *numbers, int count) {
    if (numbers == NULL || count <= 0) {
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        if (numbers[i] % 2 == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'numbers1' can be declared as const array [constVariable]
     */
    int numbers1[] = {1, 3, 5, 7, 9};
    /* Possible weaknesses found:
     *  Variable 'numbers2' can be declared as const array [constVariable]
     */
    int numbers2[] = {1, 3, 5, 7, 8};
    /* Possible weaknesses found:
     *  Variable 'numbers3' can be declared as const array [constVariable]
     */
    int numbers3[] = {2, 4, 6};
    /* Possible weaknesses found:
     *  Variable 'numbers4' can be declared as const array [constVariable]
     */
    int numbers4[] = {1, 2, 3, 4, 5};
    
    printf("Product 1 is %s\n", is_product_even(numbers1, 5) ? "even" : "odd");
    printf("Product 2 is %s\n", is_product_even(numbers2, 5) ? "even" : "odd");
    printf("Product 3 is %s\n", is_product_even(numbers3, 3) ? "even" : "odd");
    printf("Product 4 is %s\n", is_product_even(numbers4, 5) ? "even" : "odd");
    printf("Null test: %d\n", is_product_even(NULL, 5));
    printf("Zero count test: %d\n", is_product_even(numbers1, 0));
    
    return 0;
}