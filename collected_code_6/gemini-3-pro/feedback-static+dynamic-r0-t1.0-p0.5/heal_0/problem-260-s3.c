#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long long nsw_sequence(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    long long a = 1;
    long long b = 1;
    long long c = 0;
    for (int i = 2; i <= n; i++) {
        c = 2 * b + a;
        a = b;
        b = c;
    }
    return c;
}

long long nth_nsw_prime(int n) {
    if (n <= 0) return -1;
    int count = 0;
    int i = 0;
    long long nsw_val = 0;
    
    while (count < n) {
        nsw_val = nsw_sequence(i);
        if (is_prime(nsw_val)) {
            count++;
        }
        i++;
        if (i > 50) {
            return -1;
        }
    }
    return nsw_val;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val <= 0 || val > 10) {
        fprintf(stderr, "Invalid input. Please provide a positive integer (max 10 due to overflow).\n");
        return EXIT_FAILURE;
    }

    long long result = nth_nsw_prime((int)val);

    if (result == -1) {
        fprintf(stderr, "Error calculating the %ldth NSW prime (possible overflow).\n", val);
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}