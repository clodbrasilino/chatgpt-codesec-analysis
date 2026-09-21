#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

double average_of_even_numbers(int n) {
    if (n < 2 || n % 2 != 0) {
        return 0.0;
    }
    
    int count = n / 2;
    double sum = 0.0;
    
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }
    
    return sum / count;
}

int main(void) {
    int n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[32];
    size_t input_size = sizeof(input);
    
    printf("Enter an even number: ");
    if (fgets(input, input_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, input_size);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    } else if (len == input_size - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
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