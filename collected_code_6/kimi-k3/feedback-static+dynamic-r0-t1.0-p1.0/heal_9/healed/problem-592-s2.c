#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

int64_t binomial_coefficient(int64_t n, int64_t k)
{
    if (k < 0 || k > n || n < 0) {
        return 0;
    }
    
    if (k > n - k) {
        k = n - k;
    }
    
    int64_t result = 1;
    for (int64_t i = 0; i < k; i++) {
        if (result > INT64_MAX / (n - i)) {
            return -1;
        }
        result = result * (n - i) / (i + 1);
    }
    
    return result;
}

int64_t sum_of_product_binomial(int64_t n)
{
    if (n < 0 || n > 62) {
        return -1;
    }
    
    int64_t sum = 0;
    for (int64_t i = 0; i <= n; i++) {
        int64_t coeff = binomial_coefficient(n, i);
        if (coeff == -1) {
            return -1;
        }
        
        if (coeff > 0) {
            if (coeff > INT64_MAX / coeff) {
                return -1;
            }
            int64_t square = coeff * coeff;
            if (sum > INT64_MAX - square) {
                return -1;
            }
            sum += square;
        }
    }
    
    return sum;
}

int main(void)
{
    int64_t n;
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;
    char *endptr;
    
    printf("Enter the value of n: ");
    
    line_length = getline(&buffer, &buffer_size, stdin);
    if (line_length == -1) {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (line_length > 0 && buffer[line_length - 1] == '\n') {
        buffer[line_length - 1] = '\0';
    }
    
    errno = 0;
    n = strtoimax(buffer, &endptr, 10);
    
    if (endptr == buffer || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    free(buffer);
    
    int64_t result = sum_of_product_binomial(n);
    if (result == -1) {
        fprintf(stderr, "Error: Invalid input or overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("Sum of product of binomial coefficients: %" PRId64 "\n", result);
    
    return EXIT_SUCCESS;
}