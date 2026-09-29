#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long findFirstFactorialDivisible(long long x) {
    if (x <= 1) {
        return 1;
    }

    long long result = 0;
    long long tempX = x;

    for (long long p = 2; p * p <= tempX; p++) {
        if (tempX % p == 0) {
            long long count = 0;
            while (tempX % p == 0) {
                count++;
                tempX /= p;
            }

            long long low = 1, high = p * count;
            long long ans = high;

            while (low <= high) {
                long long mid = low + (high - low) / 2;
                long long currentCount = 0;
                long long temp = mid;

                while (temp > 0) {
                    currentCount += temp / p;
                    temp /= p;
                }

                if (currentCount >= count) {
                    ans = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            if (ans > result) {
                result = ans;
            }
        }
    }

    if (tempX > 1) {
        if (tempX > result) {
            result = tempX;
        }
    }

    return result;
}

int main(void) {
    long long x;

    if (scanf("%lld", &x) != 1) {
        return EXIT_FAILURE;
    }

    if (x <= 0) {
        return EXIT_FAILURE;
    }

    long long result = findFirstFactorialDivisible(x);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}