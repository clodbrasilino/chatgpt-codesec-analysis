#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

bool check_product_equal(int n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[12];
    int written = snprintf(str, sizeof(str), "%d", n);
    
    if (written < 0 || written >= (int)sizeof(str)) {
        return false;
    }
    
    int len = written;
    
    if (len <= 0) {
        return false;
    }
    
    int64_t even_product = 1;
    int64_t odd_product = 1;

    for (int i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
        int digit = str[i] - '0';
        if (digit == 0) {
            continue;
        }
        if (i % 2 == 0) {
            if (even_product > INT64_MAX / digit) {
                return false;
            }
            even_product *= digit;
        } else {
            if (odd_product > INT64_MAX / digit) {
                return false;
            }
            odd_product *= digit;
        }
    }

    return even_product == odd_product;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32] = {0};
    char *endptr;
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else if (len == sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     *  Variable 'all_zeros' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'all_zeros' can be reduced. [variableScope]
     */
    bool all_zeros = true;
    for (size_t i = 0; i < len; i++) {
        if (input[i] != '0') {
            /* Possible weaknesses found:
             *  Variable 'all_zeros' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'all_zeros' is never read [deadcode.DeadStores]
             */
            all_zeros = false;
            break;
        }
    }
    
    errno = 0;
    long val = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int num = (int)val;

    if (check_product_equal(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}