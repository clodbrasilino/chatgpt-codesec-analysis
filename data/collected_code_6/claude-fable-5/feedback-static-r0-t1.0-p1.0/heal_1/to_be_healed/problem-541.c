#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int is_abundant(unsigned long n)
{
    unsigned long sum;
    unsigned long i;

    if (n < 12UL) {
        return 0;
    }

    sum = 1UL;
    for (i = 2UL; i * i <= n; i++) {
        if (n % i == 0UL) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
            if (sum > n) {
                return 1;
            }
        }
    }

    return (sum > n) ? 1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long number;

    printf("Enter a positive integer: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoul(buffer, &endptr, 10);

    if (endptr == buffer || errno != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (number == 0UL) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }

    if (is_abundant(number)) {
        printf("%lu is an abundant number\n", number);
    } else {
        printf("%lu is not an abundant number\n", number);
    }

    return EXIT_SUCCESS;
}