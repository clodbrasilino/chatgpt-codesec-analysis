#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

unsigned long long cube_sum_natural_numbers(int n) {
    if (n < 0) {
        return 0;
    }
    
    unsigned long long sum = 0;
    unsigned long long nn = (unsigned long long)n;
    unsigned long long temp1, temp2;
    
    temp1 = nn * nn;
    temp2 = (nn + 1) * (nn + 1);
    
    if (nn > 0 && temp1 > ULLONG_MAX / nn) {
        return 0;
    }
    if (nn > ULLONG_MAX - 1) {
        return 0;
    }
    if (temp1 > ULLONG_MAX / temp2) {
        return 0;
    }
    
    sum = (temp1 * temp2) / 4;
    
    return sum;
}

int main(void) {
    char input[65] = {0};
    char *endptr;
    long long_val;
    size_t len;
    
    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strcspn(input, "\n");
    
    if (input[len] == '\n') {
        input[len] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
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