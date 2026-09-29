#include <stdio.h>
#include <stdlib.h>

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
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "n must be a positive integer.\n");
        return 1;
    }

    long long result = sum_of_squares_even(n);
    printf("%lld\n", result);

    return 0;
}