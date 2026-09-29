#include <stdio.h>
#include <stdlib.h>

static int is_valid_triangle(long a, long b, long c)
{
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a <= c - b || a <= b - c || b <= a - c) {
        return 0;
    }
    return 1;
}

static int is_isosceles(long a, long b, long c)
{
    if (!is_valid_triangle(a, b, c)) {
        return -1;
    }
    if (a == b || b == c || a == c) {
        return 1;
    }
    return 0;
}

int main(void)
{
    long a;
    long b;
    long c;
    int result;

    printf("Enter three side lengths: ");

    if (scanf("%ld %ld %ld", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = is_isosceles(a, b, c);

    if (result == -1) {
        fprintf(stderr, "Error: the given sides do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }

    return EXIT_SUCCESS;
}