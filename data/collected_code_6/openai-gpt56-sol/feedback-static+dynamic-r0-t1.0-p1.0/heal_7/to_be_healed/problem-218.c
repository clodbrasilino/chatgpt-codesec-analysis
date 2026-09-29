#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 6
  */

static unsigned long long minimum_operations(long long first, long long second)
{
    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    return (unsigned long long)second - (unsigned long long)first;
}

static int read_long_long(long long *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char extra;
    long long parsed;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (sscanf(buffer, " %lld %c", &parsed, &extra) != 1) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    long long first;
    long long second;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[512];
    char extra;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(buffer, " %lld %lld %c", &first, &second, &extra) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}