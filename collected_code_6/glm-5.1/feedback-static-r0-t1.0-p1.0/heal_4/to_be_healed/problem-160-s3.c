#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int find_solution(int a, int b, int n, int *x, int *y) {
    if (a == 0 && b == 0) {
        return (n == 0) ? 0 : -1;
    }
    if (a == 0) {
        if (n % b == 0) {
            *x = 0;
            *y = n / b;
            return 0;
        }
        return -1;
    }
    if (b == 0) {
        if (n % a == 0) {
            *x = n / a;
            *y = 0;
            return 0;
        }
        return -1;
    }
    for (int i = -abs(n); i <= abs(n); i++) {
        if ((n - a * i) % b == 0) {
            *x = i;
            *y = (n - a * i) / b;
            return 0;
        }
    }
    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <n>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    errno = 0;
    long val_a = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val_a < INT_MIN || val_a > INT_MAX) {
        return 1;
    }

    errno = 0;
    long val_b = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val_b < INT_MIN || val_b > INT_MAX) {
        return 1;
    }

    errno = 0;
    long val_n = strtol(argv[3], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || val_n < INT_MIN || val_n > INT_MAX) {
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
        printf("No solution\n");
        return 1;
    }
}