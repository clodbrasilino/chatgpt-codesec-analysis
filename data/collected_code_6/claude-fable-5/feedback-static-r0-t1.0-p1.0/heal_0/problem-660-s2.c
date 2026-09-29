#include <stdio.h>
#include <stdlib.h>

int choose_points(long long l1, long long r1, long long l2, long long r2,
                  long long *a, long long *b)
{
    if (a == NULL || b == NULL) {
        return -1;
    }
    if (l1 >= r1 || l2 >= r2) {
        return -1;
    }

    *a = l1;
    *b = r2;

    if (*a == *b) {
        *a = r1;
    }

    return 0;
}

int main(void)
{
    long long l1;
    long long r1;
    long long l2;
    long long r2;
    long long a;
    long long b;

    printf("Enter l1 r1 l2 r2: ");
    if (scanf("%lld %lld %lld %lld", &l1, &r1, &l2, &r2) != 4) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (choose_points(l1, r1, l2, r2, &a, &b) != 0) {
        fprintf(stderr, "Invalid ranges: each range must satisfy l < r\n");
        return EXIT_FAILURE;
    }

    printf("Point from first range: %lld\n", a);
    printf("Point from second range: %lld\n", b);

    return EXIT_SUCCESS;
}