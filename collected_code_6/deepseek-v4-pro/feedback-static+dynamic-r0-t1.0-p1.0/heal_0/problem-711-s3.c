#include <stdio.h>
#include <stdlib.h>

int check_product_equal(long long num) {
    if (num < 0) num = -num;
    
    long long even_product = 1;
    long long odd_product = 1;
    int position = 1;
    
    while (num > 0) {
        int digit = num % 10;
        if (position % 2 == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }
        num /= 10;
        position++;
    }
    
    return even_product == odd_product;
}

int main(void) {
    long long number;
    
    printf("Enter a number: ");
    if (scanf("%lld", &number) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (check_product_equal(number)) {
        printf("Product of digits at even and odd places is equal\n");
    } else {
        printf("Product of digits at even and odd places is not equal\n");
    }
    
    return EXIT_SUCCESS;
}