#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_prime(long n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long ns_w(long n, long x, long y) {
    if (n == 0) return x;
    if (n == 1) return y;
    return 2 * ns_w(n - 1, x, y) + ns_w(n - 2, x, y);
}

bool is_newman_shanks_williams_prime(long n) {
    return is_prime(ns_w(n, 1, 1));
}

long find_nth_ns_w_prime(int n) {
    int count = 0;
    long i = 0;
    while (true) {
        if (is_newman_shanks_williams_prime(i)) {
            count++;
            if (count == n) {
                return ns_w(i, 1, 1);
            }
        }
        i++;
    }
}

int main() {
    int n;
    printf("Enter the nth Newman–Shanks–Williams prime to find: ");
    scanf("%d", &n);
    if (n <= 0) {
        fprintf(stderr, "The input should be a positive integer.\n");
        return EXIT_FAILURE;
    }
    long result = find_nth_ns_w_prime(n);
    printf("The %dth Newman–Shanks–Williams prime is: %ld\n", n, result);
    return EXIT_SUCCESS;
}