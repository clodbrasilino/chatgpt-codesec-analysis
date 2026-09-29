#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long sum_of_digits(long long n) {
    long long sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int num_digits(long long n) {
    int count = 0;
    if (n == 0) return 1;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

void maximize_digit_sum(long long n, long long *part1, long long *part2) {
    if (n < 0) {
        *part1 = 0;
        *part2 = 0;
        return;
    }
    
    int digits = num_digits(n);
    if (digits == 1) {
        *part1 = n;
        *part2 = 0;
        return;
    }

    long long a = 0;
    for (int i = 0; i < digits - 1; i++) {
        a = a * 10 + 9;
    }

    if (a >= n) {
        a = 0;
        for (int i = 0; i < digits - 2; i++) {
            a = a * 10 + 9;
        }
    }

    long long b = n - a;
    
    if (sum_of_digits(a) + sum_of_digits(b) > sum_of_digits(n)) {
        *part1 = a;
        *part2 = b;
    } else {
        *part1 = n;
        *part2 = 0;
    }
}

int main(void) {
    long long n;
    long long part1, part2;

    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    maximize_digit_sum(n, &part1, &part2);

    printf("%lld %lld\n", part1, part2);

    return EXIT_SUCCESS;
}