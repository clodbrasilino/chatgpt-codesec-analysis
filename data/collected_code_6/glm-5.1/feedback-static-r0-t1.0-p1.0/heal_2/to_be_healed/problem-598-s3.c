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
    int temp = num;

    if (temp == 0) {
        digits = 1;
    } else {
        while (temp != 0) {
            digits++;
            temp /= 10;
        }
    }

    temp = num;
    while (temp != 0) {
        int remainder = temp % 10;
        sum += calculate_power(remainder, digits);
        temp /= 10;
    }

    if (sum == original) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        fprintf(stderr, "Invalid input. Please provide a valid positive integer.\n");
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