#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 2
  *  test case 0 failed: expected 1, got 0
  *  test case 2 failed: expected 17, got 14
  */

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    if (n == 0) {
        return 1;
    }
    unsigned long long count = 0;
    int num_bits = sizeof(n) * 8;
    for (int i = 0; i < num_bits; i++) {
        unsigned long long m = 1ULL << i;
        unsigned long long next_power = m << 1;
        unsigned long long full_cycles = (n + 1) / next_power;
        unsigned long long remainder = (n + 1) % next_power;
        unsigned long long zeros_in_complete_cycle = (full_cycles / 2) * next_power;
        unsigned long long partial_zeros = 0;
        if (full_cycles % 2 != 0) {
            if (remainder > m) {
                partial_zeros = remainder - m;
            } else {
                partial_zeros = 0;
            }
        }
        count += zeros_in_complete_cycle + partial_zeros;
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    unsigned long long n;
    if (argc != 2) {
        if (fscanf(stdin, "%llu", &n) != 1) {
            return EXIT_FAILURE;
        }
    } else {
        char *endptr;
        n = strtoull(argv[1], &endptr, 10);
        if (*endptr != '\0' || n == ULLONG_MAX) {
            return EXIT_FAILURE;
        }
    }
    unsigned long long result = count_unset_bits_up_to_n(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}