#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_prime(long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long newman_shanks_williams(long n) {
    long a = 1, b = 1;
    for (long i = 2; i <= n; ++i) {
        long temp = b;
        b = 2 * b + a;
        a = temp;
    }
    return b;
}

long find_nth_nsw_prime(long n) {
    long count = 0;
    long i = 1;
    while (true) {
        long candidate = newman_shanks_williams(i);
        if (is_prime(candidate)) {
            ++count;
            if (count == n) {
                return candidate;
            }
        }
        ++i;
    }
}

int main() {
    long n;
    printf("Enter the nth Newman–Shanks–Williams prime to find: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    long result = find_nth_nsw_prime(n);
    printf("The %ldth Newman–Shanks–Williams prime is: %ld\n", n, result);

    return EXIT_SUCCESS;
}