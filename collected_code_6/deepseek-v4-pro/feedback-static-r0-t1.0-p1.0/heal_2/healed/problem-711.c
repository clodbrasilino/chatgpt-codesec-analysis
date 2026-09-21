#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int check_product_equal(int n) {
    char str[24];
    int result = snprintf(str, sizeof(str), "%d", n);
    
    if (result < 0 || (size_t)result >= sizeof(str)) {
        return 0;
    }
    
    size_t len = strnlen(str, sizeof(str));
    if (len == 0 || len >= sizeof(str)) {
        return 0;
    }
    
    long long even_product = 1;
    long long odd_product = 1;
    size_t i;

    for (i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        int digit = str[i] - '0';
        if (digit == 0) {
            if (i % 2 == 0) {
                even_product = 0;
            } else {
                odd_product = 0;
            }
            continue;
        }
        if (i % 2 == 0) {
            if (even_product > LLONG_MAX / digit) {
                return 0;
            }
            even_product *= digit;
        } else {
            if (odd_product > LLONG_MAX / digit) {
                return 0;
            }
            odd_product *= digit;
        }
    }

    return even_product == odd_product;
}

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (num == 0) {
        printf("Product of digits at even and odd places are not equal\n");
        return EXIT_SUCCESS;
    }

    if (check_product_equal(num)) {
        printf("Product of digits at even and odd places are equal\n");
    } else {
        printf("Product of digits at even and odd places are not equal\n");
    }

    return EXIT_SUCCESS;
}