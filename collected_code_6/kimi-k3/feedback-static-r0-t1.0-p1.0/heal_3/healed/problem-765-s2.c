#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int is_polite(unsigned long long num) {
    unsigned long long temp = num;
    while ((temp & 1) == 0) {
        temp >>= 1;
    }
    return temp > 1;
}

unsigned long long find_nth_polite(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    
    unsigned long long count = 0;
    unsigned long long num = 1;
    
    while (count < n) {
        if (is_polite(num)) {
            count++;
            if (count == n) {
                return num;
            }
        }
        
        if (num == ULLONG_MAX) {
            return 0;
        }
        num++;
    }
    
    return 0;
}

int main(void) {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_len;
    char *endptr;
    unsigned long long n;
    
    read_len = getline(&input, &input_size, stdin);
    if (read_len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
    }
    
    errno = 0;
    n = strtoull(input, &endptr, 10);
    
    if (errno == ERANGE || endptr == input) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid input\n");
            free(input);
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    if (n == 0) {
        fprintf(stderr, "n must be positive\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    unsigned long long result = find_nth_polite(n);
    
    if (result == 0) {
        fprintf(stderr, "Result overflow or not found\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    free(input);
    return EXIT_SUCCESS;
}