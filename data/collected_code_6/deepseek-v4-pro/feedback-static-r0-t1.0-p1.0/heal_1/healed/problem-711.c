#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_product_equal(int n) {
    char str[20];
    snprintf(str, sizeof(str), "%d", n);
    size_t len = strnlen(str, sizeof(str));
    if (len >= sizeof(str)) {
        return 0;
    }
    
    int even_product = 1;
    int odd_product = 1;
    size_t i;

    for (i = 0; i < len; i++) {
        int digit = str[i] - '0';
        if (digit == 0) {
            continue;
        }
        if (i % 2 == 0) {
            even_product *= digit;
        } else {
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