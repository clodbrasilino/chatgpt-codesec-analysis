#include <stdio.h>
#include <limits.h>
#include <errno.h>

long long sum_of_squares(unsigned int n) {
    long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        if (sum > LLONG_MAX - (long long)i * i) {
            errno = ERANGE;
            return -1;
        }
        sum += (long long)i * i;
    }
    return sum;
}

int main() {
    unsigned int n;
    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        return 1;
    }
    errno = 0;
    long long result = sum_of_squares(n);
    if (errno == ERANGE) {
        printf("Overflow occurred\n");
        return 1;
    }
    printf("Sum of squares: %lld\n", result);
    return 0;
}