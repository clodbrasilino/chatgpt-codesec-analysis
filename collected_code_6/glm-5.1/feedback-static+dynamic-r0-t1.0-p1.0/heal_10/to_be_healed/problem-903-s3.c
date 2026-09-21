#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 6
  *  test case 2 failed: expected 17, got 27
  */

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    if (n == 0) {
        return 1;
    }
    unsigned long long count = 0;
    unsigned long long p = 1;
    while (p <= n) {
        unsigned long long full_cycles = (n + 1) / (p * 2);
        count += full_cycles * p;
        unsigned long long remainder = (n + 1) % (p * 2);
        if (remainder > p) {
            count += remainder - p;
        }
        if (p > ULLONG_MAX / 2) {
            break;
        }
        p *= 2;
    }
    return count - 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    unsigned long long n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    char *endptr;
    errno = 0;
    n = strtoull(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input or out of range\n");
        return 1;
    }
    unsigned long long result = count_unset_bits_up_to_n(n);
    printf("%llu\n", result);
    fflush(stdout);
    return 0;
}