#include <stdio.h>
#include <stdlib.h>

int checkProductEquality(long long n) {
    if (n < 0) {
        n = -n;
    }
    
    int evenProd = 1;
    int oddProd = 1;
    int position = 1;
    
    if (n == 0) {
        return 0;
    }
    
    while (n > 0) {
        int digit = n % 10;
        if (position % 2 == 0) {
            evenProd *= digit;
        } else {
            oddProd *= digit;
        }
        position++;
        n /= 10;
    }
    
    return evenProd == oddProd;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    long long num;
    
    if (argc == 2) {
        char *endptr;
        num = strtoll(argv[1], &endptr, 10);
        if (*endptr != '\0') {
            return EXIT_FAILURE;
        }
    } else if (argc == 1) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return EXIT_FAILURE;
        }
        char *endptr;
        num = strtoll(buffer, &endptr, 10);
        if (endptr == buffer || (*endptr != '\0' && *endptr != '\n')) {
            return EXIT_FAILURE;
        }
    } else {
        return EXIT_FAILURE;
    }
    
    int result = checkProductEquality(num);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}