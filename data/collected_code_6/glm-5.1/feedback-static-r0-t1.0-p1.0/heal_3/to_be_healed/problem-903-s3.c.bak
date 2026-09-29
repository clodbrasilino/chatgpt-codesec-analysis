#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    if (n == 0) {
        return 0;
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
        p *= 2;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
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
    return 0;
}