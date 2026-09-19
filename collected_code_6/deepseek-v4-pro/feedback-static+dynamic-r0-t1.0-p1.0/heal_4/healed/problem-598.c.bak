#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int int_pow(int base, int exp) {
    int result = 1;
    int i;

    if (exp < 0) {
        return -1;
    }

    if (base == 0 && exp == 0) {
        return 1;
    }

    for (i = 0; i < exp; i++) {
        if (base != 0 && result > INT_MAX / base) {
            return -1;
        }
        if (base != 0 && result < INT_MIN / base) {
            return -1;
        }
        result *= base;
    }
    return result;
}

int is_armstrong(int number) {
    int original;
    int result = 0;
    int digits = 0;

    if (number < 0) {
        return 0;
    }

    original = number;

    if (original == 0) {
        digits = 1;
    } else {
        while (original != 0) {
            original /= 10;
            digits++;
        }
    }

    original = number;

    while (original != 0) {
        int remainder = original % 10;
        int pow_result;

        if (digits == 0) {
            return 0;
        }

        pow_result = int_pow(remainder, digits);
        if (pow_result == -1) {
            return 0;
        }

        if (result > INT_MAX - pow_result) {
            return 0;
        }

        result += pow_result;
        original /= 10;
    }

    return result == number;
}

int main() {
    int num;
    char input[32];

    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Invalid input\n");
        return 1;
    }

    char *endptr;
    long val = strtol(input, &endptr, 10);

    if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        printf("Invalid input\n");
        return 1;
    }

    if (val > INT_MAX || val < INT_MIN) {
        printf("Invalid input\n");
        return 1;
    }

    num = (int)val;

    if (is_armstrong(num)) {
        printf("%d is an Armstrong number\n", num);
    } else {
        printf("%d is not an Armstrong number\n", num);
    }

    return 0;
}