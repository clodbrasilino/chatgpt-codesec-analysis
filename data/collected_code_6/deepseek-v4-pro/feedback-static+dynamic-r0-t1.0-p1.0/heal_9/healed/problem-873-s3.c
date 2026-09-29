#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long fibonacci(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        long long temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    
    if (errno == ERANGE || *endptr != '\0' || endptr == argv[1] || val < 0 || val > 40) {
        fprintf(stderr, "Error: Invalid input. Provide an integer between 0 and 40.\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    long long result = fibonacci(n);
    
    if (result == -1) {
        fprintf(stderr, "Error: Computation failed.\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}