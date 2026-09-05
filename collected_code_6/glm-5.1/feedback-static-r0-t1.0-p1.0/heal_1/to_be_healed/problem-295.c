#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_of_divisors(unsigned long long n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long sum = 0;

    for (unsigned long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    unsigned long long num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    num = strtoull(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", sum_of_divisors(num));
    return EXIT_SUCCESS;
}