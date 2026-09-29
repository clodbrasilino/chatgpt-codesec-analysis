#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

bool check_product_equal(int n) {
    char str[24];
    int written = snprintf(str, sizeof(str), "%d", n);
    if (written < 0 || written >= (int)sizeof(str)) {
        return false;
    }
    
    int len = written;
    long long even_product = 1;
    long long odd_product = 1;

    for (int i = 0; i < len; i++) {
        int digit = str[i] - '0';
        if (digit < 0 || digit > 9) {
            return false;
        }
        if (digit == 0) {
            continue;
        }
        if (i % 2 == 0) {
            if (even_product > LLONG_MAX / digit) {
                return false;
            }
            even_product *= digit;
        } else {
            if (odd_product > LLONG_MAX / digit) {
                return false;
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
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}