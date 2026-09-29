#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

bool is_prime(long num) {
    if (num <= 1) return false;
    if (num % 2 == 0) return num == 2;
    for (long i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

long newman_shanks_williams(long n) {
    long a = 1, b = 1;
    for (long i = 1; ; i++) {
        long c = 4 * a + b;
        a = b;
        b = c;
        if (is_prime(c)) {
            if (i == n) return c;
        }
        if (c > LONG_MAX / 4) break;
    }
    return -1;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    long result = newman_shanks_williams(n);
    if (result != -1) {
        printf("The %dth Newman–Shanks–Williams prime number is: %ld\n", n, result);
    } else {
        printf("Could not find the %dth Newman–Shanks–Williams prime number.\n", n);
    }
    return 0;
}