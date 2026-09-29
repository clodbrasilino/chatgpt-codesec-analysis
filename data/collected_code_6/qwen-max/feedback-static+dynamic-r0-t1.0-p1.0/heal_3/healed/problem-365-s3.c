#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int count_digits(long num) {
    if (num == 0) return 1;
    if (num == LLONG_MIN) return 20; // Special case for LLONG_MIN
    if (num < 0) num = -num;
    int count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Number of digits: %d\n", count_digits(number));
    return 0;
}