#include <stdio.h>
#include <stdlib.h>

int check_product_even_odd_places(unsigned long long n) {
    if (n == 0) {
        return 1; 
    }

    unsigned long long temp = n;
    int count = 0;
    while (temp > 0) {
        count++;
        temp /= 10;
    }

    unsigned long long product_even = 1;
    unsigned long long product_odd = 1;
    int position = count; 

    temp = n;
    while (temp > 0) {
        int digit = temp % 10;
        if (position % 2 == 0) {
            product_even *= digit;
        } else {
            product_odd *= digit;
        }
        temp /= 10;
        position--;
    }

    return (product_even == product_odd);
}

int main(void) {
    unsigned long long number;
    
    if (scanf("%llu", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (check_product_even_odd_places(number)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return EXIT_SUCCESS;
}