#include <stdio.h>
#include <stdlib.h>

int sum_odd_factors(int n) {
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            if (i != n / i) {
                if ((n / i) % 2 != 0) {
                    sum += n / i;
                }
            }
        }
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n <= 0) {
        fprintf(stderr, "Number must be a positive integer\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", sum_odd_factors(n));
    return EXIT_SUCCESS;
}