#include <stdio.h>
#include <stdlib.h>

long long fibonacci(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        long long temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int n = atoi(argv[1]);
    long long result = fibonacci(n);
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}