#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int check_product_equal(int n) {
    char str[24];
    int written = snprintf(str, sizeof(str), "%d", n);
    if (written < 0 || written >= (int)sizeof(str)) {
        return 0;
    }
    
    int len = written;
    int even_product = 1;
    int odd_product = 1;

    for (int i = 0; i < len; i++) {
        int digit = str[i] - '0';
        if (digit == 0) {
            continue;
        }
        if (i % 2 == 0) {
            if (even_product > INT_MAX / digit) {
                return 0;
            }
            even_product *= digit;
        } else {
            if (odd_product > INT_MAX / digit) {
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

    if (check_product_equal(num)) {
        printf("Product of digits at even and odd places are equal\n");
    } else {
        printf("Product of digits at even and odd places are not equal\n");
    }

    return EXIT_SUCCESS;
}