#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_armstrong(unsigned long long num) {
    unsigned long long sum = 0;
    unsigned long long original = num;
    int digits = 0;
    unsigned long long powers[10];
    unsigned long long temp = num;
    int i;

    if (num == 0) {
        return 1;
    }

    while (temp > 0) {
        temp /= 10;
        digits++;
    }

    for (i = 0; i < 10; i++) {
        unsigned long long power = 1;
        int j;
        for (j = 0; j < digits; j++) {
            if (power > ULLONG_MAX / i) {
                return 0;
            }
            power *= i;
        }
        powers[i] = power;
    }

    temp = num;
    while (temp > 0) {
        int digit = temp % 10;
        if (sum > ULLONG_MAX - powers[digit]) {
            return 0;
        }
        sum += powers[digit];
        temp /= 10;
    }

    return (sum == original);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    char *endptr;
    unsigned long long num;
    long long input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoll(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == argv[1] || input < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    num = (unsigned long long)input;

    if (is_armstrong(num)) {
        printf("%llu is an Armstrong number\n", num);
    } else {
        printf("%llu is not an Armstrong number\n", num);
    }

    return EXIT_SUCCESS;
}