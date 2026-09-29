#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 1 failed: expected 4, got 7
  *  test case 2 failed: expected 17, got 28
  */

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    unsigned long long count = 0;
    unsigned long long range = n + 1;
    /* Possible weaknesses found:
     *  Assignment 'num_bits=sizeof(n)*8', assigned value is 64
     */
    int num_bits = sizeof(n) * 8;
    /* Possible weaknesses found:
     *  Assuming that condition 'i<num_bits' is not redundant
     */
    for (int i = 0; i < num_bits; i++) {
        /* Possible weaknesses found:
         *  Shifting 64-bit value by 64 bits is undefined behaviour [shiftTooManyBits]
         *  Shift
         */
        unsigned long long next_power = 1ULL << (i + 1);
        unsigned long long full_cycles = range / next_power;
        unsigned long long remainder = range % next_power;
        unsigned long long zeros_in_complete_cycle = full_cycles << i;
        unsigned long long partial_zeros = 0;
        unsigned long long half_power = 1ULL << i;
        if (remainder > half_power) {
            partial_zeros = remainder - half_power;
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