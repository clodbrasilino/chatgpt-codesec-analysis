#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

unsigned long long sum_of_divisors(unsigned long long num)
{
    unsigned long long sum;
    unsigned long long i;

    if (num < 1ULL) {
        return 0ULL;
    }
    if (num == 1ULL) {
        return 0ULL;
    }

    sum = 1ULL;
    for (i = 2ULL; i <= num / i; i++) {
        if (num % i == 0ULL) {
            unsigned long long pair = num / i;
            sum += i;
            if (pair != i) {
                sum += pair;
            }
        }
    }
    return sum;
}

unsigned long long sum_amicable_numbers(unsigned long long limit)
{
    unsigned long long total;
    unsigned long long n;

    if (limit < 1ULL) {
        return 0ULL;
    }

    total = 0ULL;
    for (n = 1ULL; n <= limit; n++) {
        unsigned long long s = sum_of_divisors(n);
        if (s != n && s >= 1ULL && s <= limit) {
            if (sum_of_divisors(s) == n) {
                total += n;
            }
        }
    }
    return total;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    unsigned long long limit;
    unsigned long long result;
    char *p;
    size_t len;
    size_t remaining;
    int truncated;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    truncated = 0;

    if (len > 0 && buffer[len - 1] != '\n') {
        if (feof(stdin)) {
            buffer[len] = '\0';
        } else {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
                ;
            }
            truncated = 1;
        }
    } else if (len > 0) {
        buffer[len - 1] = '\0';
        len--;
    }

    if (truncated) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    p = buffer;
    remaining = len;
    while (remaining > 0 && isspace((unsigned char)*p)) {
        p++;
        remaining--;
    }

    if (*p == '\0' || remaining == 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(p, &endptr, 10);
    if (errno != 0 || endptr == p) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    while (*endptr != '\0' && isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = sum_amicable_numbers(limit);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}