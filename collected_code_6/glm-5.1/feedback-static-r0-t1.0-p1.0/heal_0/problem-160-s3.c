#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <n>\n", argv[0]);
        return 1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int n = atoi(argv[3]);
    int x, y;
    if (find_solution(a, b, n, &x, &y) == 0) {
        printf("%d %d\n", x, y);
        return 0;
    } else {
        printf("No solution\n");
        return 1;
    }
}