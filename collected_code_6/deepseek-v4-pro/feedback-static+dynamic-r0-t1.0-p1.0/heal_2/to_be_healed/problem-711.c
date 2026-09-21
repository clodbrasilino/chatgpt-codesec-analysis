#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int check_product_equal(int n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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