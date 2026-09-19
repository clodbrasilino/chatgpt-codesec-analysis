#include <stdio.h>
#include <stdlib.h>

double average_of_cubes(int n) {
    if (n <= 0) {
        return 0.0;
    }
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i * i;
    }
    return (double)sum / n;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 1290) {
        fprintf(stderr, "Error: n must be a positive integer <= 1290\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    double avg = average_of_cubes(n);
    printf("%f\n", avg);
    return EXIT_SUCCESS;
}