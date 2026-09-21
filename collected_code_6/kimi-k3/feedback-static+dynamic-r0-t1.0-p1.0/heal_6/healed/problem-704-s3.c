#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

double harmonic_sum(int n)
{
    double sum = 0.0;
    int i;
    
    if (n <= 0) {
        return 0.0;
    }
    
    for (i = 1; i <= n; i++) {
        sum += 1.0 / (double)i;
    }
    
    return sum;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    char *endptr;
    long value;
    int n;
    double result;
    
    bytes_read = getline(&buffer, &buffer_size, stdin);
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        fprintf(stderr, "Input out of range\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input format\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    n = (int)value;
    
    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    result = harmonic_sum(n);
    
    printf("%.15f\n", result);
    
    free(buffer);
    return EXIT_SUCCESS;
}