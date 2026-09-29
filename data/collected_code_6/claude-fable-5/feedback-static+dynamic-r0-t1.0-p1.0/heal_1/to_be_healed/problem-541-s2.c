#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool is_abundant(unsigned long n)
{
    unsigned long sum;
    unsigned long i;

    if (n < 2UL) {
        return false;
    }

    sum = 1UL;
    for (i = 2UL; i * i <= n; i++) {
        if (n % i == 0UL) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum > n;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long value;

    printf("Enter a positive integer: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    endptr = NULL;
    value = strtoul(buffer, &endptr, 10);

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_abundant(value)) {
        printf("%lu is an abundant number\n", value);
    } else {
        printf("%lu is not an abundant number\n", value);
    }

    return EXIT_SUCCESS;
}