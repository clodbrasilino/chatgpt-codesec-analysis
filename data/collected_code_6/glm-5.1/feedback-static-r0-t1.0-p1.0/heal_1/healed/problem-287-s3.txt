#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_of_squares_even(int n) {
    if (n <= 0) {
        return 0;
    }

    long long sum = 0;
    int count = 0;
    int num = 2;

    while (count < n) {
        sum += (long long)num * num;
        num += 2;
        count++;
    }

    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0 || val > INT_MAX) {
        fprintf(stderr, "n must be a positive integer within valid range.\n");
        return 1;
    }

    int n = (int)val;
    long long result = sum_of_squares_even(n);
    printf("%lld\n", result);

    return 0;
}