#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#define INPUT_BUFFER_SIZE 64

static unsigned long long cube_sum_natural_numbers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long nn = (unsigned long long)n;
    
    if (nn == 0) {
        return 0;
    }
    
    if (nn > ULLONG_MAX / nn) {
        return 0;
    }
    unsigned long long temp1 = nn * nn;
    
    if (nn > ULLONG_MAX - 1) {
        return 0;
    }
    
    unsigned long long nn_plus_1 = nn + 1;
    
    if (nn_plus_1 > ULLONG_MAX / nn_plus_1) {
        return 0;
    }
    unsigned long long temp2 = nn_plus_1 * nn_plus_1;
    
    if (temp2 == 0) {
        return 0;
    }
    if (temp1 > ULLONG_MAX / temp2) {
        return 0;
    }
    
    unsigned long long sum = (temp1 * temp2) / 4;
    
    return sum;
}

int main(void) {
    char input[INPUT_BUFFER_SIZE + 1];
    char *endptr;
    long long_val;
    size_t len;
    
    memset(input, 0, sizeof(input));
    
    printf("Enter a positive integer: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strcspn(input, "\n");
    
    if (len >= sizeof(input) - 1) {
        if (input[sizeof(input) - 1] != '\0') {
            input[sizeof(input) - 1] = '\0';
        }
        if (input[sizeof(input) - 2] != '\n' && input[sizeof(input) - 2] != '\0') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
        len = strnlen(input, sizeof(input));
    } else {
        if (input[len] == '\n') {
            input[len] = '\0';
        }
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long_val = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || long_val < 0 || long_val > INT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_natural_numbers((int)long_val);
    printf("Cube sum of first %d natural numbers: %llu\n", (int)long_val, result);
    
    return EXIT_SUCCESS;
}