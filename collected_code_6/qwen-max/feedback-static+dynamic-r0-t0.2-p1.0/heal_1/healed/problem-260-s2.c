#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

bool is_prime(long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long ns_williams_prime(int n) {
    if (n <= 0) return -1;
    long a = 1, b = 1;
    int count = 0;
    while (true) {
        long next = 2 * b + a;
        a = b;
        b = next;
        if (is_prime(next)) {
            count++;
            if (count == n) return next;
        }
        if (next > LONG_MAX / 2) break;
    }
    return -1;
}

int main() {
    int n;
    printf("Enter the nth Newman–Shanks–Williams prime number to find: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    long result = ns_williams_prime(n);
    if (result != -1) {
        printf("The %dth Newman–Shanks–Williams prime number is: %ld\n", n, result);
    } else {
        printf("Unable to find the requested prime number.\n");
    }
    return 0;
}