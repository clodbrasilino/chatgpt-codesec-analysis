#include <stdio.h>
#include <stdlib.h>

double average_of_even_numbers(int n) {
    if (n < 2 || n % 2 != 0) {
        return 0.0;
    }
    
    int count = n / 2;
    long sum = 0;
    
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }
    
    return (double)sum / count;
}

int main(void) {
    int n;
    char input[32];
    
    printf("Enter an even number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    char *endptr;
    n = strtol(input, &endptr, 10);
    
    if (endptr == input || *endptr != '\n') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 2 || n % 2 != 0) {
        fprintf(stderr, "Number must be even and greater than 0\n");
        return EXIT_FAILURE;
    }
    
    double avg = average_of_even_numbers(n);
    printf("Average of even numbers up to %d: %.2f\n", n, avg);
    
    return EXIT_SUCCESS;
}