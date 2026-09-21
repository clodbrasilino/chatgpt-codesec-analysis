#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

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
    char buffer[BUFFER_SIZE];
    char *endptr;
    long value;
    int n;
    double result;
    size_t len;
    char *ptr;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strlen(buffer);
    
    if (len == 0) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    ptr = buffer;
    while (isspace((unsigned char)*ptr)) {
        ptr++;
    }
    
    if (*ptr == '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtol(ptr, &endptr, 10);
    
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == ptr) {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }
    
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    n = (int)value;
    
    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        return EXIT_FAILURE;
    }
    
    result = harmonic_sum(n);
    
    printf("%.15f\n", result);
    
    return EXIT_SUCCESS;
}