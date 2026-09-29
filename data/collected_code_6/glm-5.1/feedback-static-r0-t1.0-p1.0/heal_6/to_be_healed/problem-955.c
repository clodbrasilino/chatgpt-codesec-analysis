#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_abundant(int n) {
    if (n <= 1) {
        return 0;
    }
    
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
        if (sum > n) {
            return 1;
        }
    }
    
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || val < 2 || val > INT_MAX) {
        fprintf(stderr, "Error: Invalid input. Provide an integer between 2 and %d.\n", INT_MAX);
        return 1;
    }
    
    int num = (int)val;
    
    if (is_abundant(num)) {
        printf("%d is an abundant number.\n", num);
    } else {
        printf("%d is not an abundant number.\n", num);
    }
    
    return 0;
}