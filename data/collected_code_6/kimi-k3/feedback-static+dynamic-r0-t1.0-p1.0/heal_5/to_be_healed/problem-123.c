#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

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
    char buffer[64];
    char *endptr;
    unsigned long long limit;
    unsigned long long result;
    char *p;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    p = buffer;
    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '\0') {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    limit = strtoull(p, &endptr, 10);
    if (errno != 0 || endptr == p) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*endptr)) {
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