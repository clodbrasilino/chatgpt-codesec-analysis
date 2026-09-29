#include <stdio.h>
#include <stdlib.h>

int find_min_sum_of_factors(int num) {
    if (num <= 1) {
        return num;
    }

    int sum = 0;
    int n = num;

    while (n % 2 == 0) {
        sum += 2;
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            sum += i;
            n /= i;
        }
    }

    if (n > 1) {
        sum += n;
    }

    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val <= 0) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    int result = find_min_sum_of_factors((int)val);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}