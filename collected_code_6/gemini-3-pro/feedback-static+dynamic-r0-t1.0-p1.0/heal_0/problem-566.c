#include <stdio.h>
#include <stdlib.h>

unsigned int sum_of_digits(unsigned int n);

unsigned int sum_of_digits(unsigned int n) {
    unsigned int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main(void) {
    unsigned int number = 0;
    unsigned int result = 0;

    if (scanf("%u", &number) != 1) {
        return EXIT_FAILURE;
    }

    result = sum_of_digits(number);

    if (printf("%u\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}