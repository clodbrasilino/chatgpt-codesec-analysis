#include <stdio.h>
#include <stdlib.h>

int find_min_sum_of_factors(int n) {
    if (n <= 1) {
        return n;
    }

    int sum = 0;
    int remaining = n;

    for (int i = 2; i * i <= remaining; i++) {
        while (remaining % i == 0) {
            sum += i;
            remaining /= i;
        }
    }

    if (remaining > 1) {
        sum += remaining;
    }

    return sum;
}

int main(int argc, char const * const argv[]) {
    int n;

    if (argc == 2) {
        n = atoi(argv[1]);
    } else {
        if (scanf("%d", &n) != 1) {
            return EXIT_FAILURE;
        }
    }

    int result = find_min_sum_of_factors(n);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}