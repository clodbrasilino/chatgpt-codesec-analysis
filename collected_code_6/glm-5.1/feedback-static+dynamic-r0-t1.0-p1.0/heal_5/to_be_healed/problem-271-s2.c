#include <stdio.h>
#include <stdlib.h>

long long sum_fifth_power_even(int n) {
    if (n <= 0) {
        return 0;
    }

    long long total = 0;
    for (int i = 1; i <= n; i++) {
        long long even_val = 2LL * i;
        long long power = even_val * even_val * even_val * even_val * even_val;
        total += power;
    }
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 1000000) {
        return EXIT_FAILURE;
    }

    long long result = sum_fifth_power_even((int)val);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}