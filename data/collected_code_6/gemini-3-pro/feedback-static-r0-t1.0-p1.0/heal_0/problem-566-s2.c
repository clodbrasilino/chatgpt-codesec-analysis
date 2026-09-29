#include <stdio.h>
#include <stdlib.h>

unsigned int sum_of_digits(unsigned int n);

int main(void) {
    unsigned int number = 0;

    printf("Enter a non-negative integer: ");
    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of digits: %u\n", sum_of_digits(number));

    return EXIT_SUCCESS;
}

unsigned int sum_of_digits(unsigned int n) {
    unsigned int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}