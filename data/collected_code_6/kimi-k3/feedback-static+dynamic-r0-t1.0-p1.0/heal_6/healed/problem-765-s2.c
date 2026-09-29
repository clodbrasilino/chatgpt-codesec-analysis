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
    
    if (n == 1) {
        return 3;
    }
    
    unsigned long long k = 0;
    unsigned long long temp = n;
    
    while (temp > 0) {
        temp >>= 1;
        k++;
    }
    
    if (k >= 64) {
        return 0;
    }
    
    unsigned long long power_of_2 = 1ULL << k;
    unsigned long long m = n - power_of_2;
    
    if (m == 0) {
        if (power_of_2 >= ULLONG_MAX - 1) {
            return 0;
        }
        return power_of_2 + 1;
    }
    
    if (m > (ULLONG_MAX - power_of_2 - 1) / 2) {
        return 0;
    }
    
    return power_of_2 + 2 * m + 1;
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
    
    size_t len = (size_t)read_len;
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    int has_space = 0;
    for (size_t i = 0; i < len; i++) {
        if (isspace((unsigned char)input[i])) {
            has_space = 1;
            break;
        }
    }
    
    if (has_space) {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtoull(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    if (n == 0) {
        fprintf(stderr, "n must be positive\n");
        free(input);
        return EXIT_FAILURE;
    }
    
    unsigned long long result = find_nth_polite(n);
    
    free(input);
    
    if (result == 0) {
        fprintf(stderr, "Result overflow or not found\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}