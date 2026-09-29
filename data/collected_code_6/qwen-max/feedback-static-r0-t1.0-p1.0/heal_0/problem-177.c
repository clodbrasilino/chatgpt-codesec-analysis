#include <stdio.h>
#include <stdlib.h>

long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long lcm(long a, long b) {
    return (a / gcd(a, b)) * b;
}

int find_two_numbers_within_lcm_range(long l, long r) {
    for (long i = l; i <= r; i++) {
        for (long j = i + 1; j <= r; j++) {
            if (lcm(i, j) >= l && lcm(i, j) <= r) {
                printf("Two numbers: %ld and %ld\n", i, j);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    long l, r;
    printf("Enter the range (l r): ");
    int ret = scanf("%ld %ld", &l, &r);
    if (ret != 2 || l > r) {
        fprintf(stderr, "Invalid input. Please enter two integers where the first is less than or equal to the second.\n");
        return EXIT_FAILURE;
    }

    if (find_two_numbers_within_lcm_range(l, r) == 0) {
        printf("No such pair found in the given range.\n");
    }

    return EXIT_SUCCESS;
}