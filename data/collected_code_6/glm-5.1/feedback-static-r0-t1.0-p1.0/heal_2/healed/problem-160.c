#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_solution(int a, int b, int n, int *x, int *y) {
    for (int i = 0; i <= abs(n); i++) {
        for (int j = 0; j <= abs(n); j++) {
            if (a * i + b * j == n) {
                *x = i;
                *y = j;
                return 0;
            }
            if (a * i - b * j == n) {
                *x = i;
                *y = -j;
                return 0;
            }
            if (-a * i + b * j == n) {
                *x = -i;
                *y = j;
                return 0;
            }
            if (-a * i - b * j == n) {
                *x = -i;
                *y = -j;
                return 0;
            }
        }
    }
    return -1;
}

int main(int argc, char const * const * argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <n>\n", argv[0]);
        return 1;
    }

    char *endptr_a, *endptr_b, *endptr_n;
    long val_a = strtol(argv[1], &endptr_a, 10);
    long val_b = strtol(argv[2], &endptr_b, 10);
    long val_n = strtol(argv[3], &endptr_n, 10);

    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_n != '\0') {
        fprintf(stderr, "Invalid input: arguments must be integers\n");
        return 1;
    }

    if (val_a < INT_MIN || val_a > INT_MAX || val_b < INT_MIN || val_b > INT_MAX || val_n < INT_MIN || val_n > INT_MAX) {
        fprintf(stderr, "Invalid input: integer overflow\n");
        return 1;
    }

    int a = (int)val_a;
    int b = (int)val_b;
    int n = (int)val_n;

    int x, y;
    if (find_solution(a, b, n, &x, &y) == 0) {
        printf("%d %d\n", x, y);
        return 0;
    } else {
        fprintf(stderr, "No solution found\n");
        return 1;
    }
}