#include <stdio.h>
#include <stdlib.h>

long long get_power(long long n, long long p) {
    long long count = 0;
    while (n > 0) {
        count += n / p;
        n /= p;
    }
    return count;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 5, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 2 failed: expected 4, got <no output>
  */

long long findFirstFactorialDivisible(long long x) {
    if (x <= 1) {
        return 1;
    }

    long long result = 1;
    long long tempX = x;

    for (long long p = 2; p * p <= tempX; ++p) {
        if (tempX % p == 0) {
            long long power = 0;
            while (tempX % p == 0) {
                power++;
                tempX /= p;
            }

            long long low = 1, high = p * power, ans = high;
            while (low <= high) {
                long long mid = low + (high - low) / 2;
                if (get_power(mid, p) >= power) {
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
    while (scanf("%lld", &x) == 1) {
        printf("%lld\n", findFirstFactorialDivisible(x));
    }
    return 0;
}