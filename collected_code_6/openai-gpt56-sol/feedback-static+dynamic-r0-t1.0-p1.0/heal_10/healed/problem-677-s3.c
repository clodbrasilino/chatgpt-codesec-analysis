#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_valid_triangle(long double a, long double b, long double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0L || b <= 0.0L || c <= 0.0L) {
        return false;
    }

    if (a > b) {
        long double tmp = a;
        a = b;
        b = tmp;
    }

    if (b > c) {
        long double tmp = b;
        b = c;
        c = tmp;
    }

    if (a > b) {
        long double tmp = a;
        a = b;
        b = tmp;
    }

    return a > c - b;
}

int main(void)
{
    long double sides[3];

    for (size_t i = 0; i < 3; ++i) {
        errno = 0;

        if (scanf("%Lf", &sides[i]) != 1 ||
            errno == ERANGE ||
            !isfinite(sides[i])) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    int ch;

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch != EOF) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_valid_triangle(sides[0], sides[1], sides[2]) ? "True" : "False");
    return EXIT_SUCCESS;
}