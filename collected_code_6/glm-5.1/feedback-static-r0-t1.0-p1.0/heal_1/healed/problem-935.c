#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(int n) {
    if (n <= 0) {
        return 0;
    }
    
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i;
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 1000000) {
        fprintf(stderr, "Error: n must be a positive integer within valid range.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    long long result = sum_of_squares(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}