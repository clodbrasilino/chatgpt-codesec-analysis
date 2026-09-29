#include <stdio.h>
#include <stdlib.h>

int choose_points(long l1, long r1, long l2, long r2, long *x, long *y)
{
    if (x == NULL || y == NULL) {
        return -1;
    }
    if (l1 > r1 || l2 > r2) {
        return -1;
    }

    *x = l1;
    *y = l2;

    if (*x != *y) {
        return 0;
    }

    if (r2 > l2) {
        *y = r2;
        return 0;
    }

    if (r1 > l1) {
        *x = r1;
        return 0;
    }

    return -1;
}

int main(void)
{
    long l1;
    long r1;
    long l2;
    long r2;
    long x;
    long y;
    int count;
    int i;
    int t;

    count = scanf("%d", &t);
    if (count != 1 || t < 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < t; i++) {
        count = scanf("%ld %ld %ld %ld", &l1, &r1, &l2, &r2);
        if (count != 4) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }

        if (choose_points(l1, r1, l2, r2, &x, &y) != 0) {
            fprintf(stderr, "No valid points exist\n");
            return EXIT_FAILURE;
        }

        if (printf("%ld %ld\n", x, y) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}