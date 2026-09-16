#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int is_valid_triangle(long long a, long long b, long long c)
{
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a > c - b + (LLONG_MAX - LLONG_MAX) && a <= LLONG_MAX) {
        if (a > c - b && b > a - c && c > b - a) {
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    long long a;
    long long b;
    long long c;
    int result;

    printf("Enter three sides of the triangle: ");
    result = scanf("%lld %lld %lld", &a, &b, &c);
    if (result != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (is_valid_triangle(a, b, c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return EXIT_SUCCESS;
}