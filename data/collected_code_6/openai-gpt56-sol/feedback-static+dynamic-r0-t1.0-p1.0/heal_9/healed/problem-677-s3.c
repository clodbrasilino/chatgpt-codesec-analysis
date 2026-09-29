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
        long double t = a;
        a = b;
        b = t;
    }
    if (b > c) {
        long double t = b;
        b = c;
        c = t;
    }
    if (a > b) {
        long double t = a;
        a = b;
        b = t;
    }

    return a > c - b;
}

int main(void)
{
    char input[1024];
    char *p;
    char *end;
    long double sides[3];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    p = input;

    for (size_t i = 0; i < 3; ++i) {
        errno = 0;
        sides[i] = strtold(p, &end);

        if (end == p || errno == ERANGE || !isfinite(sides[i])) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        p = end;
    }

    while (*p == ' ' || *p == '\t' || *p == '\n' ||
           *p == '\r' || *p == '\f' || *p == '\v') {
        ++p;
    }

    if (*p != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", is_valid_triangle(sides[0], sides[1], sides[2]) ? 1 : 0);
    return EXIT_SUCCESS;
}