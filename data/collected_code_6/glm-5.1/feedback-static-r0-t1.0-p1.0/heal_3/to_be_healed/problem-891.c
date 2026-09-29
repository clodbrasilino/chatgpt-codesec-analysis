#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_digits(long long n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[1];
    int len = snprintf(buf, 1, "%lld", n);
    return len > 0 ? len : 1;
}

int same_digits(long long a, long long b) {
    return count_digits(a) == count_digits(b);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    long long num1, num2;
    if (argc == 3) {
        char *endptr1, *endptr2;
        num1 = strtoll(argv[1], &endptr1, 10);
        num2 = strtoll(argv[2], &endptr2, 10);
        if (*endptr1 != '\0' || *endptr2 != '\0') {
            return EXIT_FAILURE;
        }
    } else if (scanf("%lld %lld", &num1, &num2) != 2) {
        return EXIT_FAILURE;
    }
    
    if (same_digits(num1, num2)) {
        printf("Same number of digits\n");
    } else {
        printf("Different number of digits\n");
    }
    
    return EXIT_SUCCESS;
}