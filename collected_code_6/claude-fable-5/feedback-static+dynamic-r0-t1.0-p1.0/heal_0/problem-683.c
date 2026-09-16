#include <stdio.h>
#include <stdbool.h>

static unsigned long long isqrt_ull(unsigned long long n)
{
    unsigned long long lo = 0;
    unsigned long long hi = n;
    unsigned long long ans = 0;

    if (hi > 4294967295ULL) {
        hi = 4294967295ULL;
    }

    while (lo <= hi) {
        unsigned long long mid = lo + (hi - lo) / 2ULL;
        unsigned long long sq = mid * mid;

        if (sq == n) {
            return mid;
        } else if (sq < n) {
            ans = mid;
            lo = mid + 1ULL;
        } else {
            if (mid == 0ULL) {
                break;
            }
            hi = mid - 1ULL;
        }
    }
    return ans;
}

static bool is_sum_of_two_squares(unsigned long long n)
{
    unsigned long long a;
    unsigned long long limit = isqrt_ull(n);

    for (a = 0ULL; a <= limit; a++) {
        unsigned long long a_sq = a * a;
        unsigned long long rem = n - a_sq;
        unsigned long long r = isqrt_ull(rem);

        if ((r * r) == rem) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    unsigned long long n;
    int scan_result;

    printf("Enter a non-negative integer: ");
    scan_result = scanf("%llu", &n);

    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (n > 4294967295ULL) {
        fprintf(stderr, "Error: input too large.\n");
        return 1;
    }

    if (is_sum_of_two_squares(n)) {
        printf("%llu can be represented as a sum of two squares.\n", n);
    } else {
        printf("%llu cannot be represented as a sum of two squares.\n", n);
    }

    return 0;
}