#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256

int64_t sum_of_odd_factors(int64_t n) {
    int64_t sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    double sqrt_n = sqrt((double)n);
    if (sqrt_n > (double)INT64_MAX) {
        return -1;
    }
    
    int64_t limit = (int64_t)sqrt_n;
    
    if (limit < 0) {
        return -1;
    }
    
    for (int64_t i = 1; i <= limit; i++) {
        if (n % i == 0) {
            if (i % 2 == 1) {
                if (sum > INT64_MAX - i) {
                    return -1;
                }
                sum += i;
            }
            
            int64_t paired_factor = n / i;
            if (paired_factor != i && paired_factor % 2 == 1) {
                if (sum > INT64_MAX - paired_factor) {
                    return -1;
                }
                sum += paired_factor;
            }
        }
    }
    
    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE] = {0};
    size_t len;
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }
    
    len = strnlen(input, sizeof(input));
    
    if (len == 0 || (len == sizeof(input) - 1 && input[len - 1] != '\n')) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Invalid input\n");
        return 1;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        if (len < sizeof(input) - 1) {
            input[len] = '\0';
        } else {
            input[sizeof(input) - 1] = '\0';
        }
    }
    
    char *endptr;
    errno = 0;
    int64_t number = strtoll(input, &endptr, 10);
    
    if (errno == ERANGE || number <= 0 || endptr == input || *endptr != '\0') {
        printf("Invalid input\n");
        return 1;
    }
    
    int64_t result = sum_of_odd_factors(number);
    if (result < 0) {
        printf("Overflow detected\n");
        return 1;
    }
    
    printf("%" PRId64 "\n", result);
    
    return 0;
}