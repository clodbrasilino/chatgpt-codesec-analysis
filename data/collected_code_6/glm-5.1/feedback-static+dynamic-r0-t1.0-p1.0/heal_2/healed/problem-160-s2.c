#include <stdio.h>
#include <stdlib.h>

int find_solution(int a, int b, int n, int *x, int *y) {
    if (a == 0 && b == 0) {
        return (n == 0) ? 0 : -1;
    }

    if (b == 0) {
        if (n % a == 0) {
            *x = n / a;
            *y = 0;
            return 0;
        }
        return -1;
    }

    if (a == 0) {
        if (n % b == 0) {
            *x = 0;
            *y = n / b;
            return 0;
        }
        return -1;
    }

    int x0 = 1, y0 = 0, x1 = 0, y1 = 1;
    int ta = a, tb = b;

    while (tb != 0) {
        int q = ta / tb;
        int temp = tb;
        tb = ta - q * tb;
        ta = temp;

        temp = x1;
        x1 = x0 - q * x1;
        x0 = temp;

        temp = y1;
        y1 = y0 - q * y1;
        y0 = temp;
    }

    if (n % ta != 0) {
        return -1;
    }

    int m = n / ta;
    *x = x0 * m;
    *y = y0 * m;

    return 0;
}

int main(int argc, char const * const * argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long va = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') return 1;
    long vb = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0') return 1;
    long vn = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0') return 1;

    int a = (int)va;
    int b = (int)vb;
    int n = (int)vn;

    if ((long)a != va || (long)b != vb || (long)n != vn) {
        return 1;
    }

    int x, y;
    if (find_solution(a, b, n, &x, &y) == 0) {
        printf("%d %d\n", x, y);
        return 0;
    }

    return 1;
}