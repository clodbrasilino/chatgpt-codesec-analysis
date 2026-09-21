#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_common_divisors(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }

    int g = gcd(a, b);
    int sum = 0;

    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            sum += i;
            if (i != g / i) {
                sum += g / i;
            }
        }
    }

    return sum;
}

int main(int argc, char const * const argv[]) {
    int a, b;

    if (argc != 3) {
        if (scanf("%d %d", &a, &b) != 2) {
            return 1;
        }
    } else {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        if (errno != 0 || endptr == argv[1] || val < 1 || val > INT_MAX) {
            return 1;
        }
        a = (int)val;

        errno = 0;
        val = strtol(argv[2], &endptr, 10);
        if (errno != 0 || endptr == argv[2] || val < 1 || val > INT_MAX) {
            return 1;
        }
        b = (int)val;
    }

    if (a <= 0 || b <= 0) {
        return 1;
    }

    int result = sum_common_divisors(a, b);
    printf("%d\n", result);

    return 0;
}