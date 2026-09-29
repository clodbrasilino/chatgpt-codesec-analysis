#include <stdio.h>
#include <stdlib.h>

int choose_points(long l1, long r1, long l2, long r2, long *p1, long *p2);

int choose_points(long l1, long r1, long l2, long r2, long *p1, long *p2)
{
    if (p1 == NULL || p2 == NULL) {
        return -1;
    }
    if (l1 > r1 || l2 > r2) {
        return -1;
    }

    *p1 = l1;

    if (l2 != *p1) {
        *p2 = l2;
        return 0;
    }
    if (r2 != *p1) {
        *p2 = r2;
        return 0;
    }
    if (r1 != l2) {
        *p1 = r1;
        *p2 = l2;
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
    long p1;
    long p2;

    printf("Enter first range (l1 r1): ");
    if (scanf("%ld %ld", &l1, &r1) != 2) {
        fprintf(stderr, "Invalid input for first range\n");
        return EXIT_FAILURE;
    }

    printf("Enter second range (l2 r2): ");
    if (scanf("%ld %ld", &l2, &r2) != 2) {
        fprintf(stderr, "Invalid input for second range\n");
        return EXIT_FAILURE;
    }

    if (choose_points(l1, r1, l2, r2, &p1, &p2) != 0) {
        fprintf(stderr, "No valid distinct points exist for the given ranges\n");
        return EXIT_FAILURE;
    }

    printf("Point from first range: %ld\n", p1);
    printf("Point from second range: %ld\n", p2);

    return EXIT_SUCCESS;
}