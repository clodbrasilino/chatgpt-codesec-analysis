#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got 31
  *  test case 1 failed: expected 4, got 9
  *  test case 0 failed: expected 1, got 3
  */

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    unsigned long long count = 0;
    int i = 0;

    while (1ULL << i <= n) {
        unsigned long long power = 1ULL << i;
        unsigned long long next_power = power * 2;
        unsigned long long total_pairs = (n + 1) / next_power;
        unsigned long long remainder = (n + 1) % next_power;

        count += total_pairs * power;
        if (remainder > power) {
            count += power;
        }

        i++;
    }

    return count;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr = NULL;
    unsigned long long n = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || (n == 0 && argv[1][0] != '0')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%llu\n", count_unset_bits_up_to_n(n));

    return 0;
}