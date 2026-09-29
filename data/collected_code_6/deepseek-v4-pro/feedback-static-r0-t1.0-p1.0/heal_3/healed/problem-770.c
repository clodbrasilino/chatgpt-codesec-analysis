#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_of_fourth_power_odd(unsigned int n) {
    unsigned long long sum = 0;
    unsigned long long odd = 1;
    unsigned int i;

    for (i = 0; i < n; ++i) {
        unsigned long long square = odd * odd;
        unsigned long long fourth = square * square;
        sum += fourth;
        odd += 2;
    }

    return sum;
}

int main(void) {
    unsigned int n;
    char input[64];
    char *endptr;
    size_t len;
    size_t input_size;

    printf("Enter the number of odd natural numbers: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input_size = sizeof(input);
    len = 0;
    while (len < input_size && input[len] != '\0') {
        len++;
    }

    if (len >= input_size) {
        input[input_size - 1] = '\0';
        len = input_size - 1;

        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        fprintf(stderr, "Input too long.\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    unsigned long temp = strtoul(input, &endptr, 10);

    if (errno == ERANGE || temp > UINT_MAX) {
        fprintf(stderr, "Invalid input. Value out of range.\n");
        return EXIT_FAILURE;
    }

    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)temp;

    printf("Sum of fourth powers of first %u odd natural numbers: %llu\n",
           n, sum_of_fourth_power_odd(n));

    return EXIT_SUCCESS;
}