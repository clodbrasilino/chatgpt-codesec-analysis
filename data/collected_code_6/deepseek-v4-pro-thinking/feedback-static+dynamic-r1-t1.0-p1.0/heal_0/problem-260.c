#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

static bool is_prime(unsigned long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (unsigned long long i = 5; i <= n / i; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

unsigned long long nth_newman_shanks_williams_prime(int n) {
    if (n <= 0) {
        errno = EINVAL;
        return 0;
    }
    unsigned long long s0 = 1;
    unsigned long long s1 = 1;
    int count = 0;
    while (1) {
        if (s1 > (ULLONG_MAX - s0) / 2) {
            errno = ERANGE;
            return 0;
        }
        unsigned long long next = 2 * s1 + s0;
        if (is_prime(next)) {
            count++;
            if (count == n) {
                return next;
            }
        }
        s0 = s1;
        s1 = next;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    errno = 0;
    unsigned long long result = nth_newman_shanks_williams_prime(n);
    if (errno != 0) {
        perror("nth_newman_shanks_williams_prime");
        return 1;
    }
    printf("%llu\n", result);
    return 0;
}