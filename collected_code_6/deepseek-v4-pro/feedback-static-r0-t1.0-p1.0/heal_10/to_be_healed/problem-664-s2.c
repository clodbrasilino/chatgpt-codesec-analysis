#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#define INPUT_BUFFER_SIZE 64

double average_of_even_numbers(int n) {
    if (n < 2 || n % 2 != 0) {
        return 0.0;
    }
    
    int count = n / 2;
    unsigned long long sum = 0;
    unsigned long long max_sum = ULLONG_MAX;
    
    for (int i = 2; i <= n; i += 2) {
        if (sum > max_sum - (unsigned long long)i) {
            return 0.0;
        }
        sum += (unsigned long long)i;
    }
    
    return (double)sum / count;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    
    printf("Enter an even number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, sizeof(input));
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (len == sizeof(input) - 1 && input[len - 1] != '\n') {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);
    
    if (errno != 0 || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    if (n < 2 || n % 2 != 0) {
        fprintf(stderr, "Number must be even and greater than 0\n");
        return EXIT_FAILURE;
    }
    
    double avg = average_of_even_numbers(n);
    printf("Average of even numbers up to %d: %.2f\n", n, avg);
    
    return EXIT_SUCCESS;
}