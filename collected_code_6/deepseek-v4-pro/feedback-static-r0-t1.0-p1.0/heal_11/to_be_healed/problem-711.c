#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <inttypes.h>

int check_product_equal(int n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[24];
    int result = snprintf(str, sizeof(str), "%d", n);
    
    if (result < 0 || (size_t)result >= sizeof(str)) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    unsigned long long even_product = 1;
    unsigned long long odd_product = 1;
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
            if (even_product > ULLONG_MAX / (unsigned long long)digit) {
                return 0;
            }
            even_product *= (unsigned long long)digit;
        } else {
            if (odd_product > ULLONG_MAX / (unsigned long long)digit) {
                return 0;
            }
            odd_product *= (unsigned long long)digit;
        }
    }

    return even_product == odd_product;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[32] = {0};
    int num;
    
    printf("Enter a number: ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input_buffer);
    if (input_len == 0 || input_len >= sizeof(input_buffer)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (input_buffer[input_len - 1] == '\n') {
        input_buffer[input_len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    char *endptr;
    errno = 0;
    long long val = strtoll(input_buffer, &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    num = (int)val;

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