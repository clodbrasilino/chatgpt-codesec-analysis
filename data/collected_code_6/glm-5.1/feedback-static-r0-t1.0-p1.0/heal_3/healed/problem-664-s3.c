#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

double find_average_even(int n) {
    if (n <= 0 || n % 2 != 0) {
        return 0.0;
    }

    int count = n / 2;
    if (count <= 0) {
        return 0.0;
    }

    long long sum = 0;
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }

    return (double)sum / count;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val <= 0 || val > INT_MAX || ((int)val) % 2 != 0) {
        return 1;
    }

    int num = (int)val;
    double avg = find_average_even(num);
    printf("%.2f\n", avg);

    return 0;
}