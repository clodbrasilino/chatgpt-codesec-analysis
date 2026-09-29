#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_undulating(long long num) {
    if (num < 100 && num > -100) {
        return 0;
    }

    long long prev_prev_digit = num % 10;
    if (prev_prev_digit < 0) prev_prev_digit = -prev_prev_digit;
    num /= 10;
    long long prev_digit = num % 10;
    if (prev_digit < 0) prev_digit = -prev_digit;
    num /= 10;

    if (prev_prev_digit == prev_digit) {
        return 0;
    }

    int direction = (prev_prev_digit > prev_digit) ? 1 : -1;

    while (num != 0) {
        long long current_digit = num % 10;
        if (current_digit < 0) current_digit = -current_digit;
        num /= 10;

        int current_direction = (prev_digit > current_digit) ? 1 : -1;

        if (current_direction == direction) {
            return 0;
        }

        if (current_digit == prev_digit) {
            return 0;
        }

        direction = current_direction;
        prev_digit = current_digit;
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    long long number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    number = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_undulating(number)) {
        printf("Undulating\n");
    } else {
        printf("Not undulating\n");
    }

    return EXIT_SUCCESS;
}