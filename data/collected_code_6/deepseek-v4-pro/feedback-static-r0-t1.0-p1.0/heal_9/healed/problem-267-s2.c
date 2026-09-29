#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

long long sum_of_squares_of_odd_numbers(int n) {
    if (n <= 0) {
        return 0;
    }
    long long nn = n;
    return nn * (2 * nn - 1) * (2 * nn + 1) / 3;
}

int main(void) {
    enum { INPUT_BUFFER_SIZE = 128 };
    char input[INPUT_BUFFER_SIZE];
    char *endptr;
    long val;
    size_t len;
    int c;
    
    printf("Enter a positive integer n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(input, sizeof(input));
    if (len == 0) {
        fprintf(stderr, "Empty input.\n");
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        c = getchar();
        if (c != '\n' && c != EOF) {
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            fprintf(stderr, "Input too long.\n");
            return EXIT_FAILURE;
        }
        input[sizeof(input) - 1] = '\0';
    }
    
    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Input value out of range.\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    if (val <= 0) {
        fprintf(stderr, "n must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of squares of first %ld odd natural numbers: %lld\n", 
           val, sum_of_squares_of_odd_numbers((int)val));
    
    return EXIT_SUCCESS;
}