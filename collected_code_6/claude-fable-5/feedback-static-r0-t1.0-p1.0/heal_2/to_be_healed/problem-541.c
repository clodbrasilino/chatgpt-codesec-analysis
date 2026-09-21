#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

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
    size_t len;
    const char *p;

    printf("Enter a positive integer: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int ch;
        int truncated = 0;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            truncated = 1;
        }
        if (truncated) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }

    p = buffer;
    while (isspace((unsigned char)*p)) {
        p++;
    }
    if (*p == '-' || *p == '+') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoul(p, &endptr, 10);

    if (endptr == p || errno != 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    if (*endptr != '\0') {
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