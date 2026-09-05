#include <stdio.h>
#include <stdlib.h>

void calculate_sum_avg(unsigned int n, unsigned long long *sum, double *avg) {
    if (sum == NULL || avg == NULL) {
        exit(EXIT_FAILURE);
    }
    *sum = (unsigned long long)n * (n + 1) / 2;
    if (n > 0) {
        *avg = (double)*sum / n;
    } else {
        *avg = 0.0;
    }
}

int main(void) {
    unsigned int n;
    unsigned long long sum;
    double avg;

    if (scanf("%u", &n) != 1) {
        return EXIT_FAILURE;
    }

    calculate_sum_avg(n, &sum, &avg);

    if (printf("Sum: %llu\nAverage: %.2f\n", sum, avg) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}