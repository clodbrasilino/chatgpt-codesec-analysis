#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

long long sum_odd_factors(long long n) {
    long long sum = 0;
    long long i;
    
    if (n <= 0) {
        return 0;
    }
    
    for (i = 1; i <= n / i; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    
    return sum;
}

int main(void) {
    long long number;
    char buffer[256];
    char *endptr;
    size_t len;
    int c;
    int input_too_long = 0;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    
    if (len == sizeof(buffer)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
            input_too_long = 1;
        }
        if (input_too_long || c == EOF) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }
    
    errno = 0;
    number = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (number <= 0) {
        fprintf(stderr, "Number must be positive\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", sum_odd_factors(number));
    
    return EXIT_SUCCESS;
}