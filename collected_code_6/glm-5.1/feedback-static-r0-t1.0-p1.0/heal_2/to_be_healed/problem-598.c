#include <stdio.h>
#include <stdlib.h>

int calculate_power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int is_armstrong(int num) {
    if (num < 0) {
        return 0;
    }

    int original = num;
    int sum = 0;
    int digits = 0;

    if (num == 0) {
        digits = 1;
    } else {
        int temp = num;
        while (temp > 0) {
            temp /= 10;
            digits++;
        }
    }

    int temp = num;
    while (temp > 0) {
        int remainder = temp % 10;
        sum += calculate_power(remainder, digits);
        temp /= 10;
    }

    return sum == original;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer format.\n");
        return EXIT_FAILURE;
    }

    if (val > 2147483647L) {
        fprintf(stderr, "Error: Integer overflow.\n");
        return EXIT_FAILURE;
    }

    int number = (int)val;

    if (is_armstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }

    return EXIT_SUCCESS;
}