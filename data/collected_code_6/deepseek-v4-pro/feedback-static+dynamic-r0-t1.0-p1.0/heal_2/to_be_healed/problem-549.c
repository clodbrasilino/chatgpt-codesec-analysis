#include <stdio.h>
#include <stdlib.h>

long long sum_of_fifth_power_of_odd_numbers(int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long odd_number = 2LL * i + 1;
        long long fifth_power = odd_number * odd_number * odd_number * odd_number * odd_number;
        sum += fifth_power;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    const char *const *args = (const char *const *)argv;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", args[0]);
        return 1;
    }

    char *endptr;
    long n = strtol(args[1], &endptr, 10);

    if (*endptr != '\0' || n <= 0 || n > 1000000) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return 1;
    }

    long long result = sum_of_fifth_power_of_odd_numbers((int)n);
    printf("%lld\n", result);

    return 0;
}