#include <stdio.h>
#include <stdlib.h>

unsigned long long perrin(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    
    unsigned long long p0 = 3;
    unsigned long long p1 = 0;
    unsigned long long p2 = 2;
    unsigned long long pn = 0;
    
    for (int i = 3; i <= n; i++) {
        pn = p0 + p1;
        p0 = p1;
        p1 = p2;
        p2 = pn;
    }
    
    return pn;
}

int main(int argc, const char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long n_long = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || n_long < 0 || n_long > 100) {
        fprintf(stderr, "Error: Invalid input. Please provide a non-negative integer (<= 100).\n");
        return EXIT_FAILURE;
    }

    int n = (int)n_long;
    unsigned long long result = perrin(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}