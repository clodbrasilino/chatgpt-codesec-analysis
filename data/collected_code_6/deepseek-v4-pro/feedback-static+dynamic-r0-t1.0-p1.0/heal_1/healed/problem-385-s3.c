#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long perrin_recursive(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    return perrin_recursive(n - 2) + perrin_recursive(n - 3);
}

int main(int argc, const char *argv[]) {
    int n;
    long long val;
    char *endptr;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtoll(argv[1], &endptr, 10);
    
    if ((errno == ERANGE && (val == LLONG_MAX || val == LLONG_MIN))
        || (errno != 0 && val == 0)) {
        fprintf(stderr, "Error: value out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: invalid integer\n");
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > INT_MAX) {
        fprintf(stderr, "Error: n must be non-negative and fit within int range\n");
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    
    printf("Perrin(%d) = %lld\n", n, perrin_recursive(n));
    
    return EXIT_SUCCESS;
}