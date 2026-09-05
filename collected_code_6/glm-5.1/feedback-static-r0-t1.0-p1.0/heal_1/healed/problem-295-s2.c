#include <stdio.h>
#include <stdlib.h>

long long sum_of_divisors(int n) {
    if (n <= 0) {
        return 0;
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 2147483647) {
        fprintf(stderr, "Error: Argument must be a valid positive integer.\n");
        return EXIT_FAILURE;
    }

    int num = (int)val;
    long long result = sum_of_divisors(num);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}