#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int safe_add(long long a, long long b, long long *result)
{
    if ((b > 0 && a > LLONG_MAX - b) || (b < 0 && a < LLONG_MIN - b)) {
        return -1;
    }
    *result = a + b;
    return 0;
}

static int perrin_sum(int n, long long *sum)
{
    long long p0 = 3;
    long long p1 = 0;
    long long p2 = 2;
    long long total = 0;
    int i;

    if (n < 0 || sum == NULL) {
        return -1;
    }

    *sum = 0;

    for (i = 0; i < n; i++) {
        long long current;
        long long next;

        if (i == 0) {
            current = p0;
        } else if (i == 1) {
            current = p1;
        } else if (i == 2) {
            current = p2;
        } else {
            if (safe_add(p0, p1, &next) != 0) {
                return -1;
            }
            p0 = p1;
            p1 = p2;
            p2 = next;
            current = next;
        }

        if (safe_add(total, current, &total) != 0) {
            return -1;
        }
    }

    *sum = total;
    return 0;
}

int main(void)
{
    int n;
    long long sum;

    printf("Enter the number of Perrin terms: ");

    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: number of terms must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (perrin_sum(n, &sum) != 0) {
        fprintf(stderr, "Error: computation failed or overflow occurred\n");
        return EXIT_FAILURE;
    }

    printf("Sum of first %d Perrin numbers: %lld\n", n, sum);

    return EXIT_SUCCESS;
}