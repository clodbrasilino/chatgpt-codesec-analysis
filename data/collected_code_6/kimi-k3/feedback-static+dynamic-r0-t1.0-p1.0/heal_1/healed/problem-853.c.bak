#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_odd_factors(long long n) {
    long long sum = 0;
    long long i;
    
    if (n <= 0) {
        return 0;
    }
    
    for (i = 1; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
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
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    number = strtoll(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || *endptr != '\n') {
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